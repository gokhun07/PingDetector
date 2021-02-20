
/**
 * @file raw-socket.hh
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-31
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <netinet/ip_icmp.h>	//Provides declarations for icmp header
#include <netinet/udp.h>	    //Provides declarations for udp header
#include <netinet/tcp.h>	    //Provides declarations for tcp header
#include <netinet/ip.h>  	    //Provides declarations for ip header
#include <sys/socket.h>
#include <arpa/inet.h>
#include "/usr/include/linux/if_ether.h"
#include "/usr/include/linux/if.h"
#include "/usr/include/linux/sockios.h"
#include "/usr/include/linux/if_packet.h"

#include <sys/ioctl.h>

/**
* @brief socket class 
* it controls the socket requests from the upper layer 
* 
*/

class raw_socket
{


   private:

        int sock_raw;
       
        bool create_socket();
        bool open_socket();
        bool close_socket();
        bool setup_socket();
        bool bind_socket();

   protected: 
            
    	struct sockaddr saddr;
	    struct in_addr in;
        struct ifreq   ifr;

   public:

        bool init_socket();
        int  get_socket() {return sock_raw;}

        struct in_addr*  get_in_addr() {return (struct in_addr*)&in;};
        struct sockaddr* get_sock_addr() {return (struct sockaddr*)&saddr;};
        
        bool receive_data (unsigned char *buff, int& len, uint32_t buff_size);
        bool send_data();

        raw_socket()
        {
            sock_raw = -1;
        };
        
        ~raw_socket()
        {

        };
};
