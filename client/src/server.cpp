#include "server.hpp"

using namespace std;

Server::Server(const char *ip,int port) :
    ip_addr(ip), dest_port(port), continue_loop(true), 
    islaunched(false), failed_connections(0)
{
}

Server::Server(string ip,int port) :
    ip_addr(ip), dest_port(port), continue_loop(true), 
    islaunched(false), failed_connections(0)
{
}

void Server::connect() {
    Logger::log()<<"Launching thread to server "<<ip_addr<<"("<<dest_port<<")"<<std::endl;
    Server* ptr=this;
    if(pthread_create(&thread,NULL,main_loop_thread,(void*)ptr)!=0) {
        Logger::log(LOG_ERROR)<<"Error while launching connection to server "<<ip_addr<<std::endl;
    }
}

int Server::get_failed_connections() {
    return failed_connections;
}

void Server::wait_for_message() {
    wait_message.wait();
}

void Server::main_loop() {
 
    while( sock.connect_to_server(ip_addr.c_str(),dest_port)!=0 && continue_loop ) {
        sleep(1);
        failed_connections++;
    }

    // if continue loop is false, while stopped because of a Server::stop call
    if(continue_loop) 
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

		string recvd_message(recv_str,message_length-1);
		size_t space_pos = recvd_message.find(' ');
		int message_size=atoi(recvd_message.substr(0,space_pos).c_str());
		recvd_message=recvd_message.substr(space_pos+1);

		if(message_length<RECV_L) {
		    received_messages_mutex.lock();
		    received_messages.push_back(recvd_message);
		    received_messages_mutex.unlock();		    
		} else {
		    char *recv2 = new char[message_size];

		    socket_mutex.lock();
		    ssize_t message_length2 = recv(sock.sock,recv2,message_size,0);    
		    socket_mutex.unlock();

		    if(message_length2!=0 && message_length2!=-1) {
			string final_string=recvd_message;
			final_string.append(recv2,message_length2);

			received_messages_mutex.lock();
			received_messages.push_back(final_string);
			received_messages_mutex.unlock();
		    }
		    delete [] recv2;

		}


            }
            wait_message.signal();
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

    stringstream ss(stringstream::out | stringstream::in);
    ss<<mes.size()<<" ";
    mes.insert(0,ss.str());

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
    empty=received_messages.empty();
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
