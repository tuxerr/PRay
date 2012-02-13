#ifndef DEF_SERVER
#define DEF_SERVER

#include <iostream>
#include <pthread.h>
#include <list>
#include <string>
#include <errno.h>
#include "logger.hpp"
#include "tcpsock.hpp"

#define DEFAULT_LISTENING_PORT 12345
#define RECV_L 3000
#define NETWORK_CLIENT_SLEEPTIME 30000

class Server {
public:
    Server(const char *ip,int port=DEFAULT_LISTENING_PORT);
    void connect();
    void stop();
    int send_message(std::string mes);
    bool has_messages();
    bool is_connected();
    std::string unstack_message();

    void main_loop();
    static void *main_loop_thread(void *This);
    
private:
    TCPSocket sock;
    std::string ip_addr;
    int dest_port;
    pthread_t thread;
    std::list<std::string> received_messages;
    Mutex socket_mutex;
    Mutex received_messages_mutex;
    bool continue_loop;
    bool islaunched;
};

#endif
