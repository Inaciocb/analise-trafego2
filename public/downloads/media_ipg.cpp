#include <tins/tins.h>
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace Tins;

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Uso: " << argv[0] << " arquivo.pcap\n";
    return 1;
  }
  const char *arquivo_pcap = argv[1];

  SnifferConfiguration configuracao;
  configuracao.set_filter("ip");
  FileSniffer capturador(arquivo_pcap, configuracao);

  bool primeiro_gap = true;
  Timestamp ts_anterior;

  uint64_t contagem = 0;
  long double media = 0, M2 = 0, M3 = 0, M4 = 0;

  capturador.sniff_loop([&](const Packet &pacote)
                        {
        const PDU* pdu = pacote.pdu();
        if (!pdu->find_pdu<IP>()) return true;

        Timestamp ts_atual = pacote.timestamp();
        if (primeiro_gap) {
            ts_anterior = ts_atual;
            primeiro_gap = false;
        } else {
            long double intervalo = (ts_atual.seconds() - ts_anterior.seconds()) * 1e6L
                                  + (ts_atual.microseconds() - ts_anterior.microseconds());
            ts_anterior = ts_atual;

            contagem++;
            long double delta = intervalo - media;
            long double delta_n = delta / contagem;
            long double delta_n2 = delta_n * delta_n;
            long double termo = delta * delta_n * (contagem - 1);

            M4 += termo * delta_n2 * (contagem*contagem - 3*contagem + 3)
                + 6 * delta_n2 * M2
                - 4 * delta_n * M3;
            M3 += termo * delta_n * (contagem - 2)
                - 3 * delta_n * M2;
            M2 += termo;
            media += delta_n;
        }
        return true; });

  if (contagem < 2)
  {
    std::cerr << "Dados insuficientes para calcular momentos.\n";
    return 1;
  }

  long double variancia = M2 / (contagem - 1);
  long double assimetria = std::sqrt((long double)contagem) * M3 / std::pow(M2, 1.5L);
  long double achatamento = (contagem * M4) / (M2 * M2) - 3.0L;

  std::cout << "Gaps considerados:         " << contagem << "\n";
  std::cout << "Média IPG (µs):            " << std::fixed << std::setprecision(2) << (double)media << "\n";
  std::cout << "Assimetria (skewness):     " << std::fixed << std::setprecision(4) << (double)assimetria << "\n";
  std::cout << "Achatamento (kurtosis):    " << std::fixed << std::setprecision(4) << (double)achatamento << "\n";
  return 0;
}
