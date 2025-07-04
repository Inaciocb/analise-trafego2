/*

g++ -std=c++17 ipg_geral.cpp -o ipg_geral \
  -I$(brew --prefix libtins)/include \
  -L$(brew --prefix libtins)/lib -ltins -lpcap


*/
// ipg_geral.cpp
#include <tins/tins.h>
#include <iostream>
#include <iomanip>

using namespace Tins;

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Uso: " << argv[0] << " arquivo_entrada.pcap\n";
    return 1;
  }
  const char *arquivo_pcap = argv[1];

  SnifferConfiguration configuracao;
  configuracao.set_filter("ip");
  FileSniffer capturador(arquivo_pcap, configuracao);

  bool primeiro_pacote = true;
  Timestamp timestamp_anterior;
  uint64_t soma_gaps = 0;
  uint64_t contagem_gaps = 0;

  capturador.sniff_loop([&](const Packet &pacote)
                        {
        const PDU* pdu = pacote.pdu();
        if (!pdu->find_pdu<IP>()) return true;

        Timestamp ts_atual = pacote.timestamp();
        if (primeiro_pacote) {
            timestamp_anterior = ts_atual;
            primeiro_pacote = false;
        } else {
            uint64_t diff_segundos = ts_atual.seconds() - timestamp_anterior.seconds();
            int64_t diff_microsegundos = ts_atual.microseconds() - timestamp_anterior.microseconds();
            uint64_t gap_microsegundos = diff_segundos * 1'000'000 + diff_microsegundos;

            soma_gaps += gap_microsegundos;
            contagem_gaps++;
            timestamp_anterior = ts_atual;
        }
        return true; });

  if (contagem_gaps == 0)
  {
    std::cerr << "Nenhum gap calculado (menos de 2 pacotes IPv4).\n";
    return 1;
  }

  double media_gap = static_cast<double>(soma_gaps) / contagem_gaps;
  std::cout << "Pacotes IPv4 processados: " << (contagem_gaps + 1) << "\n";
  std::cout << "Gaps calculados: " << contagem_gaps << "\n";
  std::cout << "IPG médio (µs): "
            << std::fixed << std::setprecision(2)
            << media_gap << "\n";
  return 0;
}