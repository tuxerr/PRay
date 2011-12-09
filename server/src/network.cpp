#include "network.h"

Network::Network(int port) : 
    listening_port(port)
{
    Logger::log()<<"Starting network activities on TCP port "<<port<<endl;
    TCPSocket accept_sock;
    accept_sock.bind_to_port(port);
  
}

Network::~Network() {
    Logger::log()<<"Stopping network activities"<<endl;
}

void Network::tcp_accept_thread() {

}

