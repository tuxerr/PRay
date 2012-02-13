#include "tcpsock.hpp"

TCPSocket::TCPSocket() {
    sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
//    fcntl(sock,F_SETFL,O_NONBLOCK);
    if(sock==INVALID_SOCKET) {
	Logger::log(LOG_ERROR)<<"Error during the creation of a TCP socket"<<std::endl;
	exit(0);
    }
}

TCPSocket::~TCPSocket() {
    shutdown(sock,SHUT_RDWR);
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
    }
}

int TCPSocket::connect_to_server(const char *ip,int port) {
    sockaddr_in conf;
    conf.sin_family=AF_INET;
    conf.sin_port=htons(port);
    conf.sin_addr.s_addr=inet_addr(ip);
    
    int connect_res = connect(sock,(sockaddr *)&conf,sizeof(conf));
    if(connect_res==-1) {
        Logger::log(LOG_ERROR)<<"Unable to connect socket to "<<ip<<"("<<port<<")"<<std::endl;
    }
    return connect_res;
}
