#include "client.h"

Client::Client(SOCKET sock,sockaddr_in &addr_info) : sock(sock), addr_info(addr_info) {
    ip_addr=string(inet_ntoa(addr_info.sin_addr));
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
    char recv_str[RECV_L]="";

    while(cont) {
	fd_set fd_sock; FD_ZERO(&fd_sock); FD_SET(sock,&fd_sock);

	struct timeval rp_time;	
	rp_time.tv_sec=0; rp_time.tv_usec=NETWORK_CLIENT_SLEEPTIME;

	int sel_res=select(sock,&fd_sock,NULL,NULL,&rp_time);

	if(sel_res==-1) {
	    Logger::log(LOG_ERROR)<<"Client "<<ip_addr<<" : TCP reception error"<<std::endl;
	} else if(sel_res>0) {

	    ssize_t message_length = recv(sock,recv_str,RECV_L,0);
            if(message_length==0) { // TCP DISCONNECT
                Logger::log(LOG_WARNING)<<"Client "<<ip_addr<<" has disconnected"<<std::endl;
            } else if(message_length==-1) {
                Logger::log(LOG_ERROR)<<"Client "<<ip_addr<<" : TCP reception error"<<std::endl;
            } else {
                received_messages.push_back(string(recv_str));
            }

	}
    }
    
}
