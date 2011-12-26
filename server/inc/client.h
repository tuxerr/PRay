#ifndef DEF_CLIENT
#define DEF_CLIENT

#include <string>
#include <list>
#include "tcpsock.h"
#include "logger.h"
#include <pthread.h>

#define NETWORK_CLIENT_SLEEPTIME 30000
#define RECV_L 3000

class Client {
 public:
    Client(SOCKET sock,sockaddr_in &addr_info,int id_number);
    ~Client();
    int send_message(string mes);
    void launch_thread();
    void main_loop();
    bool has_messages();
    string unstack_message();
    void stop();
    bool is_connected();
    int get_id();
    static void *main_loop_thread(void *This);

 private:
    SOCKET sock; 
    sockaddr_in addr_info;
    string ip_addr;
    pthread_t thread;
    std::list<std::string> received_messages;
    Mutex socket_mutex;
    Mutex received_messages_mutex;
    bool continue_loop;
    bool islaunched;
    int id_number;
};

#endif
