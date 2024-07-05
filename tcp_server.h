#ifndef TCP_SERVER
#define TCP_SERVER

#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <exception>
#include <iostream>

using namespace std::literals;

class TCPServer{

    int socketIndex;
    sockaddr_in socketAddress;
    
    public:
    TCPServer(std::string ip, int port);
    TCPServer(int port);
    void StartServer();
    void CloseServer();
    void Respond(int currentSocket);
    ~TCPServer();

};





#endif //TCP_SERVER
