#ifndef DEF_NETWORK
#define DEF_NETWORK

#include <iostream>
#include <pthread.h>
#include "logger.h"

#define DEFAULT_LISTENING_PORT 12345

class Network {
public:
    Network(int port=DEFAULT_LISTENING_PORT);
    ~Network();

private:
    int client_number;
    int listening_port;
    
};

#endif
