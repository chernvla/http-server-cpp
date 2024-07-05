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

    sockaddr_in currentAddress;
    uint currentLen;
    uint bytesReceived;
    while(true){
        int currentSocket = accept(socketIndex, (sockaddr *)&currentAddress, &currentLen);
        if(currentSocket < 0) 
            throw std::runtime_error("Unable to accept connection from"s + inet_ntoa(currentAddress.sin_addr));
        
        char buffer[UINT16_MAX] = {0};
        bytesReceived = read(currentSocket, buffer, UINT16_MAX);
        if (bytesReceived < 0)
            throw std::runtime_error("Failed to read bytes from client socket connection");

        Respond(currentSocket);

        close(currentSocket);
    }
}

std::string buildResponse()
{
    std::string htmlFile = "<!DOCTYPE html><html lang=\"en\"><body><h1> HOME </h1><p> Hello from your Server :) </p></body></html>";      
    return "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: "s + std::to_string(htmlFile.size()) + "\n\n" + htmlFile;
}

void TCPServer::Respond(int currentSocket){
    size_t bytesSent;
    std::string message = buildResponse();

    bytesSent = write(currentSocket, message.c_str(), message.size());

    if (bytesSent != message.size())
        throw std::runtime_error("Failed to sent bytes to client");
}

void TCPServer::CloseServer(){
    close(socketIndex);
}

TCPServer::~TCPServer(){
    CloseServer();
    
}