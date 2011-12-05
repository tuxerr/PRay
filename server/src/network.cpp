#include "network.h"

using namespace std;

Network::Network(int port) : client_number(0), listening_port(port) {
    logger->write()<<"Starting network. Listening on port "<<port<<endl;
}

Network::~Network() {
    logger->write()<<"Stopping network"<<endl;
}

Network::start() {
    
}

// network's main thread that listens to TCP connections on port listening_port
// and creates subthreads with the created TCP streams
Network::main_thread() {
    logger->write()<<"Starting main TCP thread"<<endl;
}
