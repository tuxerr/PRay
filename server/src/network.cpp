#include "network.h"

Network::Network(int port) : 
    listening_port(port), continue_loop(true), last_id(-1)
{
    Logger::log()<<"Starting network activities on TCP port "<<port<<endl;
    accept_sock.bind_to_port(port);
}

Network::~Network() {
    Logger::log()<<"Stopping network activities"<<endl;
}

int Network::launch() {
    Network* ptr=this;
    if(pthread_create(&thread,NULL,tcp_accept_loop_thread,(void*)ptr)!=0) {
        Logger::log(LOG_ERROR)<<"Error while launching general network thread"<<std::endl;
        return 0;
    }
    return 1;
}

void Network::purge_clients() {
    client_list_mutex.lock();

    std::map<int,Client>::iterator it=connected_clients.begin();
    while(it!=connected_clients.end()) {
        if(! it->second.is_connected() ) {
            it->second.stop();
            connected_clients.erase(it++);
        } else {
            ++it;
        }
    }

    client_list_mutex.unlock();
}

int Network::get_client_number() {
    purge_clients();
    
    return connected_clients.size();
}

void Network::tcp_accept_loop() {
    if(SOMAXCONN<NETWORK_MAX_CLIENTS) {
	max_clients=SOMAXCONN;
	Logger::log(LOG_WARNING)<<"Network max clients has been reduced from "<<NETWORK_MAX_CLIENTS<<" to "<<SOMAXCONN<<std::endl;
    }

    if(listen(accept_sock.sock,NETWORK_MAX_CLIENTS)==-1) {
	Logger::log(LOG_ERROR)<<"Unable to enable TCP listen mode : error "<<errno<<std::endl;
        continue_loop=false;
    }
    
    while(continue_loop) {
	sockaddr_in info;
	socklen_t info_size=sizeof(info);

	fd_set fd_sock; FD_ZERO(&fd_sock); FD_SET(accept_sock.sock,&fd_sock);

	struct timeval rp_time;	
	rp_time.tv_sec=0; rp_time.tv_usec=NETWORK_CLIENT_SLEEPTIME;

	int sel_res=select(accept_sock.sock+1,&fd_sock,NULL,NULL,&rp_time);

        if(sel_res==-1) {

            Logger::log(LOG_ERROR)<<"Main network thread TCP error"<<std::endl;
            continue_loop=false;
            
        } else if(sel_res>0) {

            // listening to new connections on the accept_sock socket.
            Logger::log()<<"Accepting new connections on the TCP socket"<<std::endl;
            SOCKET new_socket=accept(accept_sock.sock,(sockaddr*)&info,&info_size); 

            if(new_socket>0) { 	// a new client has been found
                Client act_client(new_socket,info,last_id+1);
                connected_clients.insert(pair<int,Client>(last_id+1,act_client));
                connected_clients.find(last_id+1)->second.launch_thread();
                last_id++;

            }
        }

    }

    Logger::log()<<"Exiting TCP general listening thread"<<std::endl;
}

void* Network::tcp_accept_loop_thread(void *This) {
    Network* netptr=(Network*)This;
    netptr->tcp_accept_loop();
    return NULL;
}

void Network::stop() {
    client_list_mutex.lock();
    for(std::map<int,Client>::iterator it=connected_clients.begin();it!=connected_clients.end();it++) {
        it->second.stop();
    }
    client_list_mutex.unlock();
    continue_loop=false;
    pthread_join(thread,NULL);
}

void Network::send_to_all(string message) {
    for(std::map<int,Client>::iterator it=connected_clients.begin();
        it!=connected_clients.end();it++) {
        it->second.send_message(message);
    }
}

std::vector<int> Network::get_client_ids() {
    std::vector<int> ret;
    for(std::map<int,Client>::iterator it=connected_clients.begin();
        it!=connected_clients.end();it++) {
        ret.push_back(it->first);
    }
    return ret;
}

int Network::get_last_connected_client_id() {
    return last_id;
}

Client* Network::get_client(int id) {
    std::map<int,Client>::iterator it=connected_clients.find(id);
    if(it==connected_clients.end()) {
        return NULL;
    } else {
        return &(it->second);
    }
}

Client* Network::get_first_nonempty_client() {
    for(std::map<int,Client>::iterator it=connected_clients.begin();
        it!=connected_clients.end();it++) {
        if(it->second.has_messages()) {
            return &(it->second);
        }
    }
    return NULL;
}
