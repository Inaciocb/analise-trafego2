#include <tins/tins.h>
#include <map>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace Tins;

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    std::cerr << "Uso: " << argv[0]
              << " arquivo_entrada.pcap arquivo_saida_cdf.csv\n";
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
        const PDU* pdu = pacote.pdu();
        if (pdu->find_pdu<IP>()) {
            uint32_t tamanho = pdu->size();
            contagem_tamanhos[tamanho]++;
        }
        return true; });

  uint64_t total_pacotes = 0;
  for (const auto &par : contagem_tamanhos)
  {
    total_pacotes += par.second;
  }

  std::ofstream saida(arquivo_csv);
  saida << "pkt_size,count,cdf\n";
  uint64_t acumulado = 0;
  for (const auto &par : contagem_tamanhos)
  {
    acumulado += par.second;
    long double cdf = (long double)acumulado / total_pacotes;
    saida << par.first << ","
          << par.second << ","
          << std::fixed << std::setprecision(6)
          << cdf << "\n";
  }
  saida.close();

  std::cout << "Dados de CDF gerados em " << arquivo_csv << "\n";
  return 0;
}
