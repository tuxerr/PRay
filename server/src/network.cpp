#include "network.h"

using namespace std;

Network::Network(int port) : client_number(0), listening_port(port) {
//    logger->write()<<"Starting network. Listening on port "<<port<<endl;
}

Network::~Network() {
//    logger->write()<<"Stopping network"<<endl;
}
