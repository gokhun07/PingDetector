/**
 * @file raw-socket.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-31
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "raw-socket.hh"
#include <iostream>
#include "../log/log.hh"
#include <string.h>

extern "C" {
     int socket (int __domain, int __type, int __protocPRINT_RECEIVED_RAW_FRAMESol) __THROW;
}

bool raw_socket::create_socket()
 {
   sock_raw = socket(AF_PACKET , SOCK_RAW , htons(ETH_P_ALL)); // 
   if (sock_raw < 0 )
   {
     print_error("SOCK_RAW cannot be created");
     return false;
   }
   
   print_chat("Socket is created with number : " + tostr(sock_raw));
   return true; 
 }
 bool raw_socket::open_socket()
{

}
 bool raw_socket::setup_socket()
 {
   int afpacketResp = -1 ;
   struct sockaddr_ll sll = {0}; // to bind socket on interface

   strcpy(ifr.ifr_name, (const char * )"enp4s0");

   print_chat("Setup Socket with the socket number " + tostr(sock_raw));
   if(afpacketResp = ioctl(sock_raw, SIOCGIFFLAGS, &ifr ) < 0 )
   {
      print_error("afpacket_setup: afpacket_get_promisc failed with : " + tostr(afpacketResp));
      return false;
   }
   
   ifr.ifr_flags |= IFF_PROMISC;
   
   if(ioctl(sock_raw,SIOCSIFFLAGS, &ifr ) < 0 )
   {
      print_error("afpacket_setup: afpacket_set_promisc failed with : " + tostr(afpacketResp));
      return false;
   }
/*
   if ((setsockopt(sock_raw, SOL_SOCKET, SO_REUSEADDR, NULL, sizeof(int))) < 0)
   {   
      print_error("afpacket_setup: setsockopt(SO_REUSEADDR) failed  ");
      return false;
   }

  if (( setsockopt(sock_raw, SOL_SOCKET, SO_REUSEPORT, NULL , sizeof(int))) < 0) 
  {   
      print_error("afpacket_setup: setsockopt(SO_REUSEPORT) failed  ");
      return false;
  }
*/
     if((afpacketResp = ioctl(sock_raw, SIOCGIFINDEX, &ifr)) == -1)
     {
        print_error("afpacket_setup: afpacket_get_bind_interface failed");
        return false;
     }
      /* Bind our raw socket to this interface */
        sll.sll_family = AF_PACKET;
        sll.sll_ifindex = ifr.ifr_ifindex;
        sll.sll_protocol = htons(ETH_P_ALL);
        
      if((afpacketResp = bind(sock_raw, (struct sockaddr *)&sll, sizeof(sll))) == -1)
      {
         print_error("afpacket_setup: afpacket_bind_interface failed ");
         return false;

      }

    return true;
 }

 bool raw_socket::close_socket()
 {
    return true;
 }

 bool raw_socket::receive_data(unsigned char *buff, int& len, uint32_t buff_size)
 {
      int saddr_size = sizeof(struct sockaddr);
      
      len = recvfrom(get_socket(), buff,  buff_size, MSG_DONTWAIT, this->get_sock_addr(), (socklen_t *)&saddr_size);
      
      if(len != -1)
      {
         return true; // packet received
      }
      
      return false; // no packet is received
 }

 bool raw_socket::send_data()
 {
    return true;

 }
 
 bool raw_socket::init_socket()
 {
     if (create_socket())
        {
            if (open_socket())
            {
                return setup_socket();
            }
        }
    return false;
 }
