/**
 * @file process_packet.cpp
 * @author ihsangokhun (onel.gokhun@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-02-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "process_packet.hh"
#include "../log/log.hh"
#include <sstream>
#include <string>
#include <algorithm> 

extern void process_ip_packets(const char *buf, std::size_t size);
/**
 * @brief 
 * 
 * @param buf 
 * @param size 
 */
void process_received_packet(const unsigned char *buf, std::size_t size)
{
    process_packet packet_obj(buf, size);
    packet_obj.check_frame((const unsigned char*)buf, size); 
}

/**
 * @brief 
 * 
 * @param buf 
 * @param size 
 * @return true 
 * @return false 
 */
bool process_packet::check_frame(const unsigned char *buf, std::size_t size)
{

    if (!check_frame_header(buf, size)) {   
        print_error("Frame Header Corrupted");
        return (false);
    }

    // IP Packet 0x0800
    if((ETHER_TYPE_CHECK_IP(eth_type)))
    {
        frame_header = PROTOCOL_HEADER::IP;
        print_chat("received packet is an IP packet");
        process_ip_packets((const char *)(buf+14), size - 14);
    }
    return true;
}

/**
 * @brief 
 * 
 * @param buf 
 * @param size 
 * @return true 
 * @return false 
 */
bool process_packet::check_frame_header(const unsigned char *buf, std::size_t size)
{

    fill_destination_MAC(buf);
    
    fill_source_MAC(buf);

    fill_ether_type(buf);
    
    return true;
}

void process_packet::fill_source_MAC(const unsigned char *buf )
{
    for (std::uint32_t src_mac = 6; src_mac < 12; src_mac++){

            this->source_MAC.push_back(buf[src_mac]);
    }

#ifdef PRINT_PACKET_CONTENT
    print_chat("Source MAC address: ");
    print_part_of_packet(source_MAC, source_MAC.size());
#endif

}

void process_packet::fill_destination_MAC(const unsigned char *buf)
{
    for (std::uint32_t src_mac = 0; src_mac < 6; src_mac++){

            this->destination_MAC.push_back(buf[src_mac]);
    }
#ifdef PRINT_PACKET_CONTENT
    print_chat("Destination MAC address: ");
    print_part_of_packet(destination_MAC, destination_MAC.size());
#endif
}

void process_packet::fill_ether_type(const unsigned char *buf)
{
    for (std::uint32_t src_mac = 12; src_mac < 14; src_mac++){

            this->eth_type.push_back(buf[src_mac]);
    }

#ifdef PRINT_PACKET_CONTENT
    print_chat("Ether Type: ");
    print_part_of_packet(eth_type, eth_type.size());
#endif

}

void process_packet::print_part_of_packet(std::vector<unsigned char> &data, size_t size)
{
    std::stringstream received_packet_stream; // string stream will be used in order to print packets as hexadecimal format 
 
    if(size <= 0)
        return;
    
    for (size_t i = 0; i < size; i++)
    {
        // fill string stream in oorder to print in hexadecimal 
        if (data.at(i) <= 16)   
            received_packet_stream << "0" << std::hex << (std::uint32_t)(data.at(i) ) << " "; 
        else
            received_packet_stream << std::hex << (std::uint32_t)(data.at(i) ) << " ";
   
    }

    std::string received_stream_to_str = received_packet_stream.str();

    std::transform(received_stream_to_str.begin(), received_stream_to_str.end(),received_stream_to_str.begin(), ::toupper);
    
    print_data(" ");
    print_data(" ");
    print_data(received_stream_to_str);
    print_data(" ");
}


/**
 * @brief constructor of process_packet class.This prints the packets that are received by the socket 
 * 
 * @param buf received packets
 * @param size size of the received packets 
 *
 */
process_packet::process_packet(const unsigned char *buf, std::size_t size)
{
 #ifdef PRINT_RECEIVED_RAW_FRAMES

    std::stringstream received_packet_stream; // string stream will be used in order to print packets as hexadecimal format 
    std::string received_packet_str;  // it is used to print received string message 


    if(size <= 0)
        return;
    
    for (size_t i = 0; i < size; i++)
    {
        // fill string stream in oorder to print in hexadecimal 
        if (buf[i] <= 16)   
            received_packet_stream << "0" << std::hex << (std::uint32_t)(buf[i]) << " "; 
        else
            received_packet_stream << std::hex << (std::uint32_t)(buf[i]) << " ";

        // print readable format
        if (buf[i]>= 32 && buf[i] <=128){
                received_packet_str += buf[i];
        }  
        else {
                received_packet_str +=".";
        }      
    }

    std::string received_stream_to_str = received_packet_stream.str();

    std::transform(received_stream_to_str.begin(), received_stream_to_str.end(),received_stream_to_str.begin(), ::toupper);
    
    print_data(" ");
    print_data(received_packet_str);
    print_data(" ");
    print_data(received_stream_to_str);
    print_data(" ");
#endif 
}

/**
 * @brief Destroy the process packet::process packet object
 * 
 */
process_packet::~process_packet()
{
}

