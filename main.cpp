#include "tcp_server.h"

int main(){
    TCPServer myServer( 80);
    myServer.StartServer();
    return 0;
}