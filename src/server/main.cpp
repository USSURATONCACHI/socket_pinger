#include <iostream>
#include <server/socket.hpp>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    std::cout << "Hello, world!" << std::endl;

    // Default ctor creates uninit socket, so we call create_socket();
    server::TcpSocket socket = server::TcpSocket(AF_INET);
    socket.bind_addr(INADDR_ANY, htons(5123));
    std::cout << "Socket created" << std::endl;

    socket.allow_listen();

    // while(true) {
        
    // }

    return 0;
}