#include <tins/tins.h>
#include <iostream>
#include <iomanip>

using namespace Tins;

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " input.pcap\n";
    return 1;
  }
  const char *pcap_file = argv[1];

  SnifferConfiguration config;
  config.set_filter("ip");
  FileSniffer sniffer(pcap_file, config);

  uint64_t total_bytes = 0;
  uint64_t total_pkts = 0;

  sniffer.sniff_loop([&](const Packet &packet)
                     {
        total_bytes += packet.pdu()->size();
        total_pkts++;
        return true; });

  if (total_pkts == 0)
  {
    std::cerr << "Nenhum pacote IPv4 encontrado.\n";
    return 1;
  }

  double avg = static_cast<double>(total_bytes) / total_pkts;
  std::cout << "Pacotes processados: " << total_pkts << "\n";
  std::cout << "Tamanho médio (bytes): "
            << std::fixed << std::setprecision(2)
            << avg << "\n";
  return 0;
}
