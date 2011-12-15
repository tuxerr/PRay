#ifndef DEF_NETWORK
#define DEF_NETWORK

#include <iostream>
#include <pthread.h>
#include <vector>
#include <string>
#include "client.h"
#include "logger.h"
#include "tcpsock.h"

#define DEFAULT_LISTENING_PORT 12345
#define NETWORK_MAX_CLIENTS 80

class Network {
public:
    Network(int port=DEFAULT_LISTENING_PORT);
    ~Network();
    int launch(pthread_t *thread);
    int get_client_number();
    void stop();
    void send_to_all(string message);

private:
    void tcp_accept_loop();

    pthread_t thread;
    TCPSocket accept_sock;
    int max_clients;
    int listening_port;
    std::vector<Client> connected_clients;
    bool continue_loop;
    Mutex client_list_mutex;
    
};

#endif
