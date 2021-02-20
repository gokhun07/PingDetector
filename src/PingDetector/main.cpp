#include <iostream> 
#include <unistd.h>

#include "../raw_socket_sniffer/raw-socket/raw-socket.hh"
#include "../raw_socket_sniffer/log/log.hh"
unsigned char recv_buff[65535];
extern void process_received_packet(const  unsigned char *buf, std::size_t size);
int main(int argc, char const *argv[])
{
    
    raw_socket sniffer_sock;

    if (sniffer_sock.init_socket())
        {
            print_chat("Socket is created with socket: " + tostr(sniffer_sock.get_socket()));
        }
    else 
        {
            print_error("Socket cannot be created");
            return 1;
        }
    
    print_chat("Starts to data receiving from the socket");

    
    int recv_data_len = 0;

    while(true)
    {
        sniffer_sock.receive_data(recv_buff,recv_data_len,65535);
        if (recv_data_len != -1)
        {
            print_chat("Received data length = " + tostr(recv_data_len));
            process_received_packet((const unsigned char*)recv_buff, recv_data_len);
            recv_data_len = 0;

            usleep(100000);
        }
    }

    return 0;
}
