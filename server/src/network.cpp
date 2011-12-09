#include "network.h"

Network::Network(int port) : 
    listening_port(port)
{
    Logger::log()<<"Starting network activities on TCP port "<<port<<endl;
    accept_sock.bind_to_port(port);
  
}

Network::~Network() {
    Logger::log()<<"Stopping network activities"<<endl;
}

void Network::tcp_accept_thread() {
    bool cont=true;
    if(SOMAXCONN<NETWORK_MAX_CLIENTS) {
	max_clients=SOMAXCONN;
	Logger::log(LOG_WARNING)<<"Network max clients has been reduced from "<<NETWORK_MAX_CLIENTS
				<<" to "<<SOMAXCONN<<std::endl;
    }

    if(listen(accept_sock.sock,MAX_CLIENTS)==-1) {
	Logger::log(LOG_ERROR)<<"Unable to enable TCP listen mode : error "<<errno<<std::endl;
	exit(0);
    }
    
    while(cont) {
	sockaddr_in info;
	socklen_t info_size=sizeof(info);

	// listening to new connections on the accept_sock socket.
	SOCKET new_socket=accept(accept_sock.sock,(sockaddr*)&info,&info_size); 

	if(new_socket>0) { 	// a new client has been found
	    // start the client thread
	}
    }

    Logger::log()<<"Exiting TCP general listening thread"<<std::endl;
}

