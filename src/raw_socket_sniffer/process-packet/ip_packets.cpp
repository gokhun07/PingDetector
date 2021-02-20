#include "ip_packets.hh"
#include "../log/log.hh"


void process_ip_packets(const char *buf, std::size_t size)
{
    struct iphdr *iph = (struct iphdr*)buf;
    
    switch (iph->protocol)
    {
    case 1: // ICMP Protocol
    print_warning("ICMP Packet Received");
    break;
    
    default:
        break;
    }

}

ip_packets::ip_packets(/* args */)
{
}

ip_packets::~ip_packets()
{
}
