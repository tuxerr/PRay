#ifndef DEF_NETWORK
#define DEF_NETWORK

#include <iostream>
#include <pthread.h>
#include <vector>
#include <map>
#include <list>
#include <string>
#include <errno.h>
#include "client.h"
#include "logger.h"
#include "tcpsock.h"

#define DEFAULT_LISTENING_PORT 12345
#define NETWORK_MAX_CLIENTS 80

class Network {
public:
    Network(int port=DEFAULT_LISTENING_PORT);
    ~Network();
    int launch();
    int get_client_number();
    void stop();
    void send_to_all(string message);
    void tcp_accept_loop();
    void purge_clients();
    std::vector<int> get_client_ids();
    int get_last_connected_client_id();
    int get_first_nonempty_client();
    Client* get_client(int id);
    static void* tcp_accept_loop_thread(void *This);
    Conditional& get_recv_cond();


private:
    pthread_t thread;
    TCPSocket accept_sock;
    int max_clients;
    int listening_port;
    std::map<int,Client> connected_clients;
    bool continue_loop;
    Mutex client_list_mutex;
    int last_id;
    Conditional recv_cond;
    
};

#endif
