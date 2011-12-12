#include "client.h"

Client::Client(SOCKET sock,sockaddr_in &addr_info) : sock(sock), addr_info(addr_info) {
    ip_addr=String(inet_ntoa(addr_info.sin_addr));
    Logger::log()<<"New client connected : "<<ip_addr<<std::endl;
}

Client::~Client() {

}

int Client::send_message(string mes) {
    
}

void Client::launch_thread() {
    Logger::log()<<"Launching TCP client "<<ip_addr<<" thread"<<std::endl;
}

void Client::main_loop() {
    bool cont=true;

    while(cont) {
	fd_set fd_sock; FD_ZERO(&fd_sock); FD_SET(sock,&fd_sock);

	struct timeval rp_time;	
	rp_time.tv_sec=0; rp_time.tv_usec=NETWORK_CLIENT_SLEEPTIME;

	int sel_res=select(sock,&fd_sock,NULL,NULL,&rp_time);

	if(sel_res==-1) {
	    Logger::log(LOG_ERROR)<<"Client "<<ip_addr<<" : TCP reception error"<<std::endl;
	} else if(sel_res>0) {
	    ssize_t message_length = recv(sock,
	}

    }
}
