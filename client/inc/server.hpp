#ifdef __linux__

#ifndef DEF_SERVER
#define DEF_SERVER

#include <iostream>
#include <pthread.h>
#include <list>
#include <string>
#include <errno.h>
#include "logger.hpp"
#include "tcpsock.hpp"
#include "conditional.hpp"

#define DEFAULT_LISTENING_PORT 12345
#define RECV_L 40
#define NETWORK_CLIENT_SLEEPTIME 30000

class Server {
public:
    Server(const char *ip,int port=DEFAULT_LISTENING_PORT);
    Server(std::string ip,int port=DEFAULT_LISTENING_PORT);
    void connect();
    void stop();
    int send_message(std::string mes);
    void wait_for_message();
    bool has_messages();
    bool is_connected();
    int get_failed_connections();
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
    int failed_connections;
    Conditional wait_message;
};

#endif

#endif
