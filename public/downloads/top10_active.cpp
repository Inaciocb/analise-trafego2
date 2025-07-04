// g++ -std=c++17 top10_ativos.cpp -o top10_ativos \
//   -I$(brew --prefix libtins)/include \
//   -L$(brew --prefix libtins)/lib -ltins -lpcap

#include <tins/tins.h>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace Tins;

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    std::cerr << "Uso: " << argv[0] << " arquivo_entrada.pcap arquivo_saida_top10.csv\n";
    return 1;
  }
  const char *arquivo_pcap = argv[1];
  const char *arquivo_csv = argv[2];

  SnifferConfiguration configuracao;
  configuracao.set_filter("ip");
  FileSniffer capturador(arquivo_pcap, configuracao);

  std::unordered_map<std::string, uint64_t> contagens;

  capturador.sniff_loop([&](const Packet &pacote)
                        {
        const IP* ip = pacote.pdu()->find_pdu<IP>();
        if (ip) {
            contagens[ip->src_addr().to_string()]++;
        }
        return true; });

  std::vector<std::pair<std::string, uint64_t>> vetor;
  vetor.reserve(contagens.size());
  for (auto &par : contagens)
  {
    vetor.emplace_back(par.first, par.second);
  }
  std::sort(vetor.begin(), vetor.end(),
            [](auto &a, auto &b)
            { return a.second > b.second; });

  std::ofstream saida(arquivo_csv);
  saida << "src_ip,packet_count\n";
  for (size_t i = 0; i < vetor.size() && i < 10; ++i)
  {
    saida << vetor[i].first << "," << vetor[i].second << "\n";
  }
  std::cout << "Top 10 IPs mais ativos gerado em " << arquivo_csv << "\n";
  return 0;
}
