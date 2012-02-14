#include "client.hpp"

Client::Client(SOCKET sock,sockaddr_in &addr_info,int id_number,Conditional &recv_cond) : 
    sock(sock), addr_info(addr_info), continue_loop(true),
    islaunched(false), id_number(id_number), recv_cond(recv_cond)
{
    ip_addr=string(inet_ntoa(addr_info.sin_addr));
    Logger::log()<<"New client connected : "<<ip_addr<<std::endl;
}

Client::~Client() {
    
}

int Client::send_message(string mes) {
    if(!is_connected()) {
        Logger::log(LOG_ERROR)<<"Error while sending TCP packet on client "<<ip_addr<<" thread : Client is disconnected"<<std::endl;
        return -1;
    }

    socket_mutex.lock();
    ssize_t message_length = send(sock,mes.c_str(),mes.size()+1,0);
    if(message_length==-1) {
        Logger::log(LOG_ERROR)<<"Error while sending TCP packet on client "<<ip_addr<<" thread"<<std::endl;
        continue_loop=false;
    }
    socket_mutex.unlock();

    return message_length;
}

bool Client::is_connected() {
    return islaunched;
}

void Client::launch_thread() {
    Logger::log()<<"Launching TCP client "<<ip_addr<<" thread"<<std::endl;
    Client* ptr=this;
    if(pthread_create(&thread,NULL,main_loop_thread,(void*)ptr)!=0) {
        Logger::log(LOG_ERROR)<<"Error while launching client "<<ip_addr<<" thread"<<std::endl;
    }
}

bool Client::has_messages() {
    if(!is_connected()) {
        return false;
    }
    bool empty;
    received_messages_mutex.lock();
    empty=received_messages.empty();
    received_messages_mutex.unlock();
    return !empty;
}

string Client::unstack_message() {
    if(!is_connected()) {
        return "";
    }
    string res;
    received_messages_mutex.lock();
    if(!received_messages.empty()) {
        res=received_messages.front();        
        received_messages.pop_front();
    } else {
        res="";
    }
    received_messages_mutex.unlock();
    return res;
}

void Client::main_loop() {
    char recv_str[RECV_L]="";
    islaunched=true;

    while(continue_loop) {

        fd_set fd_sock; FD_ZERO(&fd_sock); FD_SET(sock,&fd_sock);
	struct timeval rp_time;	
	rp_time.tv_sec=0; rp_time.tv_usec=NETWORK_CLIENT_SLEEPTIME;

	int sel_res=select(sock+1,&fd_sock,NULL,NULL,&rp_time);

	if(sel_res==-1) {
	    Logger::log(LOG_ERROR)<<"Client "<<ip_addr<<" : TCP reception error"<<std::endl;
            continue_loop=false;
	} else if(sel_res>0) {

            socket_mutex.lock();
	    ssize_t message_length = recv(sock,recv_str,RECV_L,0);    
            socket_mutex.unlock();

            if(message_length==0) { // TCP DISCONNECT
                Logger::log(LOG_WARNING)<<"Client "<<ip_addr<<" disconnected"<<std::endl;
                continue_loop=false;
            } else if(message_length==-1) {
                Logger::log(LOG_ERROR)<<"Client "<<ip_addr<<" : TCP reception error"<<std::endl;
                continue_loop=false;
            } else {
                received_messages.push_back(string(recv_str,message_length-1));
                recv_cond.signal();
            }
	}
    }

    islaunched=false;
}

int Client::get_id() {
    return id_number;
}

void* Client::main_loop_thread(void *This) {
    Client* cli_ptr=(Client*)This;
    cli_ptr->main_loop();
    return NULL;
}

void Client::stop() {
    continue_loop=false;
    pthread_join(thread,NULL);
}

