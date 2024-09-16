#include <iostream>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <thread>
#include <utility>
#include <vector>

#include <net_raii/connection.hpp>
#include <net_raii/socket.hpp>

static void handle_connection(net_raii::TcpConnection&& conn);
static void run_server(int port);

struct Params {
    int port;
};
// Returns either Params, or a string error
static Params parse_input(int argc, const char* const* argv, bool& out_error);

int main(int argc, char** argv) {
    bool had_error = false;
    Params p = parse_input(argc, argv, had_error);

    if (had_error) {
        std::cout << "Usage: " << argv[0] << " <port>" << std::endl;
        return 1;
    }
    

    run_server(p.port);
    return 0;
}

static Params parse_input(int argc, const char* const* argv, bool& out_error) {
    if (argc != 2) {
        std::cerr << "Incorrect input args" << std::endl;
        out_error = true;
        return Params();
    }

    Params result;
    try {
        result.port = std::stoi(argv[1]);
    } 
    catch (const std::invalid_argument& e) {
        out_error = true;
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    }
    catch (const std::out_of_range& e) {
        out_error = true;
        std::cerr << "Out of range exception: " << e.what() << std::endl;
    }

    return result;
}

static void run_server(int port) {
    net_raii::TcpSocket socket(AF_INET); // Ipv4

    socket.bind_addr(INADDR_ANY, htons(port));
    std::cout << "Socket created (port = " << port << ")" << std::endl;

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