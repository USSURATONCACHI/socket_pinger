#include <cassert>
#include <iostream>

#include <net_raii/connection.hpp>
#include <net_raii/socket.hpp>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT 5123

int main() {
    std::cout << "Hello, world!" << std::endl;

    net_raii::TcpSocket socket(AF_INET);
    std::cout << "Socket created" << std::endl;

    in_addr_t addr = socket.address_from_text(SERVER_ADDRESS);
    socket.connect_to_addr(addr, htons(SERVER_PORT));
    std::cout << "Socket connected" << std::endl;
}