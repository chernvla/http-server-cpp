#ifndef TCP_SERVER
#define TCP_SERVER

#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <exception>
#include <iostream>

class TCPServer{

    int socketIndex;
    sockaddr_in socketAddress;
    

    TCPServer(std::string ip, int port);
    TCPServer(int port);
    void StartServer();
    void CloseServer();
    ~TCPServer();


    public:

};





#endif //TCP_SERVER
