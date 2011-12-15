#include "network.h"

Network::Network(int port) : 
    listening_port(port), continue_loop(true)
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

int Network::get_client_number() {
    client_list_mutex.lock();
    int res= connected_clients.size();
    client_list_mutex.unlock();
    return res;
}

void Network::tcp_accept_loop() {
    if(SOMAXCONN<NETWORK_MAX_CLIENTS) {
	max_clients=SOMAXCONN;
	Logger::log(LOG_WARNING)<<"Network max clients has been reduced from "<<NETWORK_MAX_CLIENTS
				<<" to "<<SOMAXCONN<<std::endl;
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
            
        } else {

            // listening to new connections on the accept_sock socket.
            SOCKET new_socket=accept(accept_sock.sock,(sockaddr*)&info,&info_size); 

            if(new_socket>0) { 	// a new client has been found
                Client act_client(new_socket,info);
                connected_clients.push_back(act_client);
            
                // start the client thread
                connected_clients.back().launch_thread();
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
    for(std::vector<Client>::iterator it=connected_clients.begin();it!=connected_clients.end();it++) {
        (*it).stop();
    }
    client_list_mutex.unlock();
    continue_loop=false;
    pthread_join(thread,NULL);
}

void Network::send_to_all(string message) {
    client_list_mutex.lock();
    for(std::vector<Client>::iterator it=connected_clients.begin();it!=connected_clients.end();it++) {
        it->send_message(message);
    }
    client_list_mutex.unlock();
}
