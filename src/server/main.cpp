#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include <net_raii/connection.hpp>
#include <net_raii/socket.hpp>

int main() {
    std::cout << "Hello, world!" << std::endl;

    // Default ctor creates uninit socket, so we call create_socket();
    net_raii::TcpSocket socket(AF_INET);
    socket.bind_addr(INADDR_ANY, htons(5123));
    std::cout << "Socket created" << std::endl;

    socket.allow_listen();
    std::cout << "Socket listening..." << std::endl;

    while(true) {
        net_raii::TcpConnection conn = socket.accept_connection();
        std::cout << "Accepted connection." << std::endl;

        std::string msg = conn.recv();
        if (msg.length() > 0)
            std::cout << "Message: " << msg << std::endl;
        else
            std::cout << "No message" << std::endl;
    }

    return 0;
}