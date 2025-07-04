#include <tins/tins.h>
#include <iostream>
#include <map>
#include <cmath>
#include <iomanip>

using namespace Tins;

static constexpr uint64_t TAMANHO_JANELA_SEGUNDOS = 1;
static constexpr uint64_t LIMIAR_SILENCIO_SEGUNDOS = 5;

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Uso: " << argv[0] << " arquivo.pcap\n";
    return 1;
  }
  const char *caminhoPcap = argv[1];
  SnifferConfiguration configuracao;
  configuracao.set_filter("ip");
  FileSniffer analisador(caminhoPcap, configuracao);

  std::map<uint64_t, uint64_t> contagemPorJanela;
  analisador.sniff_loop([&](const Packet &pacote)
                        {
        uint64_t segundoAtual = pacote.timestamp().seconds();
        uint64_t indiceJanela = segundoAtual / TAMANHO_JANELA_SEGUNDOS;
        contagemPorJanela[indiceJanela]++;
        return true; });

  if (contagemPorJanela.empty())
  {
    std::cerr << "Nenhum pacote IPv4 encontrado.\n";
    return 1;
  }
  uint64_t primeiraJanela = contagemPorJanela.begin()->first;
  uint64_t ultimaJanela = contagemPorJanela.rbegin()->first;
  uint64_t numeroJanelas = ultimaJanela - primeiraJanela + 1;

  long double somaContagens = 0;
  long double somaContagensQuad = 0;
  for (uint64_t idx = primeiraJanela; idx <= ultimaJanela; ++idx)
  {
    long double c = contagemPorJanela.count(idx) ? contagemPorJanela[idx] : 0;
    somaContagens += c;
    somaContagensQuad += c * c;
  }
  long double mediaContagem = somaContagens / numeroJanelas;
  long double variancia = somaContagensQuad / numeroJanelas - mediaContagem * mediaContagem;
  long double desvioPadrao = std::sqrt(variancia);
  long double limiarBurst = mediaContagem + desvioPadrao;

  std::cout << "== Picos de tráfego (bursts) ==\n";
  for (uint64_t idx = primeiraJanela; idx <= ultimaJanela; ++idx)
  {
    long double c = contagemPorJanela.count(idx) ? contagemPorJanela[idx] : 0;
    if (c > limiarBurst)
    {
      std::cout << "Pico em " << (idx * TAMANHO_JANELA_SEGUNDOS)
                << "s (contagem=" << (uint64_t)c << ")\n";
    }
  }

  std::cout << "\n== Silêncios longos ≥ " << LIMIAR_SILENCIO_SEGUNDOS << "
