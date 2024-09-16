#include <iostream>
#include <sys/socket.h>
#include <thread>
#include <vector>

#include <net_raii/connection.hpp>
#include <net_raii/socket.hpp>

static void handle_connection(net_raii::TcpConnection&& conn);
static void run_server(int port);

int main() {
    run_server(5123);
    return 0;
}

static void run_server(int port) {
    net_raii::TcpSocket socket(AF_INET); // Ipv4

    socket.bind_addr(INADDR_ANY, htons(port));
    std::cout << "Socket created" << std::endl;

    socket.allow_listen();
    std::cout << "Socket listening..." << std::endl;

    while(true) {
        net_raii::TcpConnection conn = socket.accept_connection();
        std::cout << "Accepted connection." << std::endl;

        std::thread new_thread(handle_connection, std::move(conn));
        new_thread.detach();
    }
}

static void handle_connection(net_raii::TcpConnection&& conn) {
    bool has_disconnected = false;
    do {
        std::string msg = conn.recv_with_len(&has_disconnected);

        if (msg.length() > 0)
            std::cout << "Message: " << msg << std::endl;
    } while(!has_disconnected);

    std::cout << "Connection ended." << std::endl;
}