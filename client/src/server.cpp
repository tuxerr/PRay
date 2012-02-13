#include "server.hpp"

using namespace std;

Server::Server(const char *ip,int port) :
    ip_addr(ip), dest_port(port), continue_loop(true), islaunched(false)
{
}

void Server::connect() {
    Logger::log()<<"Launching thread to server "<<ip_addr<<"("<<dest_port<<")"<<std::endl;
    Server* ptr=this;
    if(pthread_create(&thread,NULL,main_loop_thread,(void*)ptr)!=0) {
        Logger::log(LOG_ERROR)<<"Error while launching connection to server "<<ip_addr<<std::endl;
    }
}

void Server::main_loop() {
 
    while(sock.connect_to_server(ip_addr.c_str(),dest_port)!=0) {
        sleep(2);
    }
    Logger::log()<<"Established connection to the server "<<ip_addr<<"("<<dest_port<<")"<<std::endl;
    
    char recv_str[RECV_L]="";
    islaunched=true;

    while(continue_loop) {
	fd_set fd_sock; FD_ZERO(&fd_sock); FD_SET(sock.sock,&fd_sock);

	struct timeval rp_time;	
	rp_time.tv_sec=0; rp_time.tv_usec=NETWORK_CLIENT_SLEEPTIME;

	int sel_res=select(sock.sock+1,&fd_sock,NULL,NULL,&rp_time);

	if(sel_res==-1) {
	    Logger::log(LOG_ERROR)<<"Server "<<ip_addr<<" : TCP reception error"<<std::endl;
            continue_loop=false;
	} else if(sel_res>0) {

            socket_mutex.lock();
	    ssize_t message_length = recv(sock.sock,recv_str,RECV_L,0);    
            socket_mutex.unlock();

            if(message_length==0) { // TCP DISCONNECT
                Logger::log(LOG_WARNING)<<"Server "<<ip_addr<<" has disconnected"<<std::endl;
                continue_loop=false;
            } else if(message_length==-1) {
                Logger::log(LOG_ERROR)<<"Server "<<ip_addr<<" : TCP reception error"<<std::endl;
                continue_loop=false;
            } else {
                received_messages.push_back(string(recv_str));
            }
	}
    }

    islaunched=false;
    Logger::log()<<"Disconnecting from server "<<ip_addr<<"("<<dest_port<<")"<<std::endl;
}

void Server::stop() {
    continue_loop=false;
    pthread_join(thread,NULL);
}

int Server::send_message(string mes) {
    socket_mutex.lock();
    ssize_t message_length = send(sock.sock,mes.c_str(),mes.size()+1,0);
    if(message_length==-1) {
        Logger::log(LOG_ERROR)<<"Error while sending TCP packet to server "<<ip_addr<<std::endl;
        continue_loop=false;
    }
    socket_mutex.unlock();

    return message_length;
}

bool Server::has_messages() {
    bool empty;
    received_messages_mutex.lock();
    empty=received_messages.empty();
    received_messages_mutex.unlock();
    return !empty;
}

bool Server::is_connected() {
    return islaunched;
}

string Server::unstack_message() {
    received_messages_mutex.lock();
    string res=received_messages.front();
    received_messages.pop_front();
    received_messages_mutex.unlock();
    return res;
}

void* Server::main_loop_thread(void *This) {
    Server* cli_ptr=(Server*)This;
    cli_ptr->main_loop();
    return NULL;
}
