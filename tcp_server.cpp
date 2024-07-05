#include "tcp_server.h"

TCPServer::TCPServer(int port){
    socketAddress.sin_port = htons(port);
    socketAddress.sin_family = AF_INET;
    socketAddress.sin_addr.s_addr = INADDR_ANY;  
}


TCPServer::TCPServer(std::string ip, int port){
    socketAddress.sin_port = htons(port);
    socketAddress.sin_family = AF_INET;
    socketAddress.sin_addr.s_addr = inet_addr(ip.c_str());   
}

void TCPServer::StartServer(){
    socketIndex = socket(AF_INET, SOCK_STREAM, 0);
    if(socketIndex < 0)
        throw std::runtime_error("Unable to create socket");
    if(bind(socketIndex, (sockaddr *)&socketAddress, sizeof(socketAddress)) < 0)
        throw std::runtime_error("Unable to bind socket");
    if (listen(socketIndex, 10) < 0)
        throw std::runtime_error("Socket listen failed");
}

void TCPServer::CloseServer(){
    close(socketIndex);
}

TCPServer::~TCPServer(){
    CloseServer();
    
}