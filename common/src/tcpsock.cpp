#include "tcpsock.h"

TCPSocket::TCPSocket() {
    sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    fcntl(sock,F_SETFL,O_NONBLOCK);
    if(sock==INVALID_SOCKET) {
	Logger::log(LOG_ERROR)<<"Error during the creation of a TCP socket"<<endl;
	exit(0);
    }
}

TCPSocket::~TCPSocket() {
    closesocket(sock);
}

void TCPSocket::bind_to_port(int port) {
    sockaddr_in conf;
    conf.sin_family=AF_INET;
    conf.sin_port=htons(port);
    conf.sin_addr.s_addr=htonl(INADDR_ANY);
    
    /* binding sock to the new sockaddr */
    if(bind(sock,(sockaddr *)&conf,sizeof(conf)) == SOCKET_ERROR) {
	Logger::log(LOG_ERROR)<<"Unable to bind socket on port "<<port<<". Exiting server"<<std::endl;
        exit(0);
    } else {
	Logger::log()<<"Socket binded to port "<<port<<std::endl;
    }
}

void TCPSocket::bind_to_port_and_ip(int port,char *ip) {
    sockaddr_in conf;
    conf.sin_family=AF_INET;
    conf.sin_port=htons(port);
    conf.sin_addr.s_addr=inet_addr(ip);
    
    /* binding sock to the new sockaddr */
    if(bind(sock,(sockaddr *)&conf,sizeof(conf)) == SOCKET_ERROR) {
	Logger::log(LOG_ERROR)<<"Unable to bind socket on port "<<port<<" and ip "<<ip<<". Exiting server"<<std::endl;
        exit(0);
    } 

}

