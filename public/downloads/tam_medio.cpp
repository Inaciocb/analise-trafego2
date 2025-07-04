#include <tins/tins.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <unordered_map>
#include <string>

using namespace Tins;

struct Stats
{
  uint64_t count = 0;
  uint64_t sum_bytes = 0;
};

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    std::cerr << "Uso: " << argv[0] << " input.pcap output_size_stats.csv\n";
    return 1;
  }
  const char *pcap_file = argv[1];
  const char *csv_file = argv[2];

  SnifferConfiguration config;
  config.set_filter("ip");
  FileSniffer sniffer(pcap_file, config);

  std::unordered_map<std::string, Stats> acc;

  sniffer.sniff_loop([&](const Packet &packet)
                     {
        const PDU* pdu = packet.pdu();
        const IP*  ip  = pdu->find_pdu<IP>();
        if (!ip) return true;

        uint32_t pkt_size = pdu->size();
        std::string src   = ip->src_addr().to_string();

        auto& st = acc[src];
        st.count++;
        st.sum_bytes += pkt_size;

        return true; });

  std::ofstream out(csv_file);
  out << "src_ip,avg_pkt_size_bytes\n";
  for (const auto &entry : acc)
  {
    const auto &ip = entry.first;
    const auto &st = entry.second;
    double avg = static_cast<double>(st.sum_bytes) / st.count;
    out << ip << "," << std::fixed << std::setprecision(2) << avg << "\n";
  }
  out.close();

  std::cout << "CSV gerado em " << csv_file << "\n";
  return 0;
}
