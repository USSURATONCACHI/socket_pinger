#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>

#include <net_raii/socket.hpp>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_ADDRESS "127.0.0.1"

int main() {
    std::string name = "Client 1";
    int server_port = 5123;
    double sending_period = 2.0;

    uint64_t period_microsec = (uint64_t)(sending_period * 1000.0 * 1000.0);

    net_raii::TcpSocket socket(AF_INET);
    std::cout << "Socket created" << std::endl;

    in_addr_t addr = socket.address_from_text(SERVER_ADDRESS);
    socket.connect_to_addr(addr, htons(server_port));
    std::cout << "Socket connected" << std::endl;

    while (true) {
        std::cout << "Sending from " << name << std::endl;
        socket.send_with_len(name + "\n");
        std::this_thread::sleep_for(std::chrono::microseconds(period_microsec));
    }
}
