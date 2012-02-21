#ifndef DEF_NETWORKRENDERER
#define DEF_NETWORKRENDERER

#define MAX_FAILED_CONNECTIONS 10

#include "server.hpp"
#include "logger.hpp"
#include <iostream>
#include <stdlib.h>

typedef enum {
    CLIENT_WAITING,
    CLIENT_RENDERING
} Client_Status;

class NetworkRenderer {
public:
    NetworkRenderer(Server &serv);
    void run();

private:
    Server &serv;
    Client_Status status;
};

#endif
