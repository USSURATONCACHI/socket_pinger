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

        char buffer[1024] = {0};
        size_t bytes_read = recv(conn.get_file_descriptor(), buffer, sizeof(buffer) - 1, 0);
        buffer[bytes_read] = '\0';

        if (bytes_read > 0)
            std::cout << "Message from client: " << buffer << std::endl;
        else
            std::cout << "Connection ended." << std::endl;
    }

    return 0;
}