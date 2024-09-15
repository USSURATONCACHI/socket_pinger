#include <iostream>

#include <sys/socket.h>
#include <unistd.h>

int main() {
    std::cout << "Hello, world!" << std::endl;

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0); // IPv4, TCP

    std::cout << "Socket created." << std::endl;

    close(socket_fd);
    std::cout << "Socket freed." << std::endl;

    return 0;
}