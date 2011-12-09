#ifndef DEF_TCPSOCK
#define DEF_TCPSOCK

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close (s)
typedef int SOCKET;
typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

class TCPSocket {
 public:
    TCPSocket();
    ~TCPSocket();
    void bind(int port);
    void bind(int port,char *ip);
    SOCKET sock;	

};

#endif
