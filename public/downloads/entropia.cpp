#include <tins/tins.h>
#include <fstream>
#include <iostream>
#include <map>
#include <unordered_map>
#include <string>

using namespace Tins;

static constexpr uint64_t TAMANHO_JANELA = 1;

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    std::cerr << "Uso: " << argv[0]
              << " arquivo_entrada.pcap arquivo_saida_dist_tempo.csv\n";
    return 1;
  }
  const char *arquivo_pcap = argv[1];
  const char *arquivo_csv = argv[2];

  SnifferConfiguration configuracao;
  configuracao.set_filter("ip");
  FileSniffer capturador(arquivo_pcap, configuracao);

  std::map<
      uint64_t,
      std::unordered_map<std::string, uint64_t>>
      contagens_por_janela;

  capturador.sniff_loop([&](const Packet &pacote)
                        {
        const PDU* pdu = pacote.pdu();
        const IP* ip = pdu->find_pdu<IP>();
        if (!ip) {
            return true;
        }
        uint64_t tempo_segundos = pacote.timestamp().seconds();
        uint64_t indice_janela = tempo_segundos / TAMANHO_JANELA;
        std::string origem = ip->src_addr().to_string();
        contagens_por_janela[indice_janela][origem]++;
        return true; });

  std::ofstream saida(arquivo_csv);
  saida << "inicio_janela,src_ip,contagem_pacotes\n";
  for (const auto &par_janela : contagens_por_janela)
  {
    uint64_t inicio_janela = par_janela.first * TAMANHO_JANELA;
    for (const auto &par_ip : par_janela.second)
    {
      saida << inicio_janela
            << "," << par_ip.first
            << "," << par_ip.second
            << "\n";
    }
  }
  saida.close();

  std::cout << "CSV de distribuição temporal gerado em "
            << arquivo_csv << "\n";
  return 0;
}
