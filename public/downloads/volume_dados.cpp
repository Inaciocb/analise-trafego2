// g++ -std=c++17 volume_dados.cpp -o volume_dados \
//   -I$(brew --prefix libtins)/include \
//   -L$(brew --prefix libtins)/lib -ltins -lpcap

#include <tins/tins.h>
#include <iostream>

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

  uint64_t total_bytes = 0;
  sniffer.sniff_loop([&](const Packet &packet)
                     {
        total_bytes += packet.pdu()->size();
        return true; });

  std::cout << "Volume TOTAL de bytes transmitidos: "
            << total_bytes << " bytes\n";
  return 0;
}
