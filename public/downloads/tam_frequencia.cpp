// g++ -std=c++17 tam_frequencia_pt.cpp -o tam_frequencia \
//   -I$(brew --prefix libtins)/include \
//   -L$(brew --prefix libtins)/lib -ltins -lpcap

#include <tins/tins.h>
#include <map>
#include <fstream>
#include <iostream>

using namespace Tins;

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    std::cerr << "Uso: " << argv[0]
              << " arquivo_entrada.pcap arquivo_saida_freq_tamanho.csv\n";
    return 1;
  }
  const char *arquivo_pcap = argv[1];
  const char *arquivo_csv = argv[2];

  SnifferConfiguration configuracao;
  configuracao.set_filter("ip");
  FileSniffer capturador(arquivo_pcap, configuracao);

  std::map<uint32_t, uint64_t> contagem_tamanhos;
  capturador.sniff_loop([&](const Packet &pacote)
                        {
        if (pacote.pdu()->find_pdu<IP>()) {
            uint32_t tamanho = pacote.pdu()->size();
            contagem_tamanhos[tamanho]++;
        }
        return true; });

  std::ofstream saida(arquivo_csv);
  saida << "pkt_size,frequencia\n";
  for (const auto &par : contagem_tamanhos)
  {
    saida << par.first << "," << par.second << "\n";
  }
  saida.close();

  std::cout << "CSV gerado em " << arquivo_csv << "\n";
  return 0;
}
