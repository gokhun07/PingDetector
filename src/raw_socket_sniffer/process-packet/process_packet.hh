/**
 * @file process_packet.hh
 * @author ihsangokhun (onel.gokhun@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-02-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream> 
#include <vector>

// linux libraries 
#include <netinet/ip_icmp.h>	//Provides declarations for icmp header
#include <netinet/udp.h>	    //Provides declarations for udp header
#include <netinet/tcp.h>	    //Provides declarations for tcp header
#include <netinet/ip.h>  	    //Provides declarations for ip header
#include <sys/socket.h>
#include <arpa/inet.h>
#include "/usr/include/linux/if_ether.h"

//#define PRINT_PACKET_CONTENT
//#define PRINT_RECEIVED_RAW_FRAMES
/**
 * @brief 
 * 
 */

#define ETHER_TYPE_CHECK_IP(x) (bool) (((x.at(0)<<8) + (x.at(1))) == 0x0800)

enum class PROTOCOL_HEADER {

    ICMP, 
    IGMP,
    IP,
    UDP,
};

/**
 * @brief 
 * 
 */
class process_packet
{
    /* private functions */
    private:
        bool check_frame_header(const unsigned char *buf, std::size_t size);
        void fill_destination_MAC(const unsigned char *buf);
        void fill_source_MAC(const unsigned char *buf);
        void fill_ether_type(const unsigned char *buf);
        
    public: 

        bool check_frame(const unsigned  char *buf, std::size_t size);
        
    /*private variables*/
    private: 
        PROTOCOL_HEADER frame_header;
        std::vector<unsigned char> source_MAC; 
        std::vector<unsigned char> destination_MAC; 
        std::vector<unsigned char> payload; 
        std::vector<unsigned char> eth_type; 

        

public:
    void print_part_of_packet(std::vector<unsigned char> &data, size_t size);
    process_packet(const unsigned char *buf, std::size_t size);
    ~process_packet();
};

