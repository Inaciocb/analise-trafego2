// g++ -std=c++17 horizontal_scan.cpp -o horizontal_scan \
//   -I$(brew --prefix libtins)/include \
//   -L$(brew --prefix libtins)/lib -ltins -lpcap

// ./horizontal_scan apenas_ip.pcap unique_dests_per_src.csv

#include <tins/tins.h>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace Tins;

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    std::cerr << "Uso: " << argv[0]
              << " arquivo_entrada.pcap arquivo_saida.csv\n";
    return 1;
  }
  const char *arquivo_pcap = argv[1];
  const char *arquivo_csv = argv[2];

  SnifferConfiguration configuracao_captura;
  configuracao_captura.set_filter("ip");
  FileSniffer analisador(arquivo_pcap, configuracao_captura);

  std::unordered_map<std::string, std::unordered_set<std::string>> destinos_por_origem;

  analisador.sniff_loop([&](const Packet &pacote)
                        {
        const IP* ip = pacote.pdu()->find_pdu<IP>();
        if (ip) {
            std::string origem = ip->src_addr().to_string();
            std::string destino = ip->dst_addr().to_string();
            destinos_por_origem[origem].insert(destino);
        }
        return true; });

  std::ofstream saida(arquivo_csv);
  saida << "src_ip,contagem_destinos_unicos\n";
  for (const auto &par : destinos_por_origem)
  {
    saida << par.first << "," << par.second.size() << "\n";
  }
  saida.close();

  size_t total_ips = destinos_por_origem.size();
  long double soma = 0;
  long double soma_quadrados = 0;
  for (const auto &par : destinos_por_origem)
  {
    long double count = par.second.size();
    soma += count;
    soma_quadrados += count * count;
  }
  long double media = soma / total_ips;
  long double variancia = soma_quadrados / total_ips - media * media;
  long double desvio_padrao = std::sqrt(variancia);
  long double limite_anomalia = media + 2 * desvio_padrao;

  std::cout << "CSV gerado em:                  " << arquivo_csv << "\n"
            << "Média de destinos únicos:      " << std::fixed << std::setprecision(2) << media << "\n"
            << "Desvio-padrão:                  " << std::fixed << std::setprecision(2) << desvio_padrao << "\n"
            << "Limite (média + 2σ):            " << std::fixed << std::setprecision(2) << limite_anomalia << "\n"
            << "\nIPs com destinos desproporcionais:\n";

  for (const auto &par : destinos_por_origem)
  {
    size_t contagem = par.second.size();
    if ((long double)contagem > limite_anomalia)
    {
      std::cout << par.first << " -> " << contagem << "\n";
    }
  }

  return 0;
}
