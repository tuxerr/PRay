#ifndef DEF_NETWORK
#define DEF_NETWORK

#include <iostream>
#include <pthread.h>
#include "logger.h"
#include "tcpsock.h"

#define DEFAULT_LISTENING_PORT 12345
#define NETWORK_MAX_CLIENTS 80

class Network {
public:
    Network(int port=DEFAULT_LISTENING_PORT);
    ~Network();

private:
    void tcp_accept_thread();

    TCPSocket accept_sock;
    int client_number;
    int max_clients;
    int listening_port;
    
};

#endif
