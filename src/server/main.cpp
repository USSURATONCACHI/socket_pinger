#include <iostream>
#include <thread>
#include <vector>

#include <net_raii/connection.hpp>
#include <net_raii/socket.hpp>

static void handle_connection(net_raii::TcpConnection&& conn);

int main() {
    std::cout << "Hello, world!" << std::endl;

    // Default ctor creates uninit socket, so we call create_socket();
    net_raii::TcpSocket socket(AF_INET);
    socket.bind_addr(INADDR_ANY, htons(5123));
    std::cout << "Socket created" << std::endl;

    socket.allow_listen();
    std::cout << "Socket listening..." << std::endl;

    std::vector<std::thread> thread_handles;

    while(true) {
        net_raii::TcpConnection conn = socket.accept_connection();
        std::cout << "Accepted connection." << std::endl;

        std::thread new_thread(handle_connection, std::move(conn));
        thread_handles.push_back(std::move(new_thread));
    }

    std::cout << "Stopping threads..." << std::endl;
    for (std::thread& t : thread_handles)
        t.join();

    return 0;
}

static void handle_connection(net_raii::TcpConnection&& conn) {
    bool has_disconnected = false;
    do {
        std::string msg = conn.recv_with_len(&has_disconnected);

        if (msg.length() > 0)
            std::cout << "Message: " << msg << std::endl;
        else
            // has_disconnected = true;
            std::cout << "No message now..." << std::endl;
    } while(!has_disconnected);

    std::cout << "Connection ended." << std::endl;
}