#include "server/connection.hpp"
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
    std::cout << "Socket listening..." << std::endl;

    while(true) {
        server::TcpConnection conn = socket.accept_connection();

        char buffer[1024] = {0};
        recv(conn.get_file_descriptor(), buffer, sizeof(buffer), 0);
        std::cout << "Message from client: " << buffer << std::endl;
    }

    return 0;
}