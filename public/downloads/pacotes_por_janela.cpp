#include <tins/tins.h>
#include <fstream>
#include <iostream>
#include <map>

using namespace Tins;

static constexpr uint64_t TAMANHO_JANELA = 1;

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    std::cerr << "Uso: " << argv[0] << " arquivo_entrada.pcap arquivo_saida_dist_janelas.csv\n";
    return 1;
  }
  const char *arquivo_pcap = argv[1];
  const char *arquivo_csv = argv[2];

  SnifferConfiguration configuracao;
  configuracao.set_filter("ip");
  FileSniffer capturador(arquivo_pcap, configuracao);

  std::map<uint64_t, uint64_t> contagens_por_janela;
  capturador.sniff_loop([&](const Packet &pacote)
                        {
        uint64_t segundo = pacote.timestamp().seconds();
        uint64_t indice = segundo / TAMANHO_JANELA;
        contagens_por_janela[indice]++;
        return true; });

  std::ofstream saida(arquivo_csv);
  saida << "inicio_janela,contagem_pacotes\n";
  for (const auto &par : contagens_por_janela)
  {
    uint64_t inicio = par.first * TAMANHO_JANELA;
    saida << inicio << "," << par.second << "\n";
  }
  saida.close();

  std::cout << "CSV gerado em " << arquivo_csv << "\n";
  return 0;
}
