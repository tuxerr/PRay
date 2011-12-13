#ifndef DEF_CLIENT
#define DEF_CLIENT

#include <string>
#include <vector>
#include "tcpsock.h"
#include "logger.h"
#include <pthread.h>

#define NETWORK_CLIENT_SLEEPTIME 30000
#define RECV_L 3000

class Client {
 public:
    Client(SOCKET sock,sockaddr_in &addr_info);
    ~Client();
    int send_message(string mes);
    void launch_thread();

 private:
    void main_loop();

    SOCKET sock; 
    sockaddr_in addr_info;
    string ip_addr;
    std::vector<std::string> received_messages;
}

#endif
