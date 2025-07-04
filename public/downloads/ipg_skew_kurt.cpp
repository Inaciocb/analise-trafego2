#include <tins/tins.h>
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace Tins;

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Uso: " << argv[0] << " input.pcap\n";
    return 1;
  }
  const char *pcap_file = argv[1];

  SnifferConfiguration config;
  config.set_filter("ip");
  FileSniffer sniffer(pcap_file, config);

  bool first = true;
  Timestamp prev_ts;

  uint64_t n = 0;
  long double mean = 0, M2 = 0, M3 = 0, M4 = 0;

  sniffer.sniff_loop([&](const Packet &packet)
                     {
        const PDU* pdu = packet.pdu();
        if (!pdu->find_pdu<IP>()) return true;

        Timestamp ts = packet.timestamp();
        if (first) {
            prev_ts = ts;
            first = false;
        } else {
            long double gap = (ts.seconds() - prev_ts.seconds()) * 1e6L
                            + (ts.microseconds() - prev_ts.microseconds());
            prev_ts = ts;

            n++;
            long double delta = gap - mean;
            long double delta_n = delta / n;
            long double delta_n2 = delta_n * delta_n;
            long double term1 = delta * delta_n * (n - 1);

            M4 += term1 * delta_n2 * (n*n - 3*n + 3)
                  + 6 * delta_n2 * M2
                  - 4 * delta_n * M3;
            M3 += term1 * delta_n * (n - 2)
                  - 3 * delta_n * M2;
            M2 += term1;
            mean += delta_n;
        }
        return true; });

  if (n < 2)
  {
    std::cerr << "Dados insuficientes para calcular momentos.\n";
    return 1;
  }

  long double variance = M2 / (n - 1);
  long double skewness = std::sqrt((long double)n) * M3 / std::pow(M2, 1.5L);
  long double kurtosis = (n * M4) / (M2 * M2) - 3.0L;

  std::cout << "Pacotes considerados (gaps): " << n << "\n";
  std::cout << "Média IPG (µs):            " << std::fixed << std::setprecision(2) << (double)mean << "\n";
  std::cout << "Skewness (assimetria):     " << std::fixed << std::setprecision(4) << (double)skewness << "\n";
  std::cout << "Kurtosis (achatamento):    " << std::fixed << std::setprecision(4) << (double)kurtosis << "\n";
  return 0;
}
