#include <fstream>
#include <iostream>
#include <mutex>
#include <thread>
#include <functional>

#include <net_raii/connection.hpp>
#include <net_raii/socket.hpp>

#include <server/parsing.hpp>
#include <server/cout_safe.hpp>


using WriteFn = std::function<void(const std::string&)>;

static void handle_connection(net_raii::TcpConnection&& conn, WriteFn* write);
static void run_server(int port, WriteFn* write);

static void write_to_file_safe(const std::string& message, std::mutex& file_mutex, std::ofstream& log_file);

int main(int argc, char** argv) {
    bool had_error = false;
    Params p = parse_input(argc, argv, had_error);

    if (had_error) {
        cout_safe("Usage: ", argv[0], " <port>");
        return 1;
    }
    
    std::mutex file_mutex;
    std::ofstream log_file("log.txt", std::ios::app);
    WriteFn write = [&file_mutex, &log_file](const std::string& msg) { 
        write_to_file_safe(msg, file_mutex, log_file);
    };

    run_server(p.port, &write);
    return 0;
}


static void run_server(int port, WriteFn* write) {
    net_raii::TcpSocket socket(AF_INET); // Ipv4

    socket.bind_addr(INADDR_ANY, htons(port));
    std::cout << "Socket created (port = " << port << ")" << std::endl;

    socket.allow_listen();
    std::cout << "Socket listening..." << std::endl;

    while(true) {
        net_raii::TcpConnection conn = socket.accept_connection();
        cout_safe("Accepted connection.\n");

        std::thread new_thread(handle_connection, std::move(conn), write);
        new_thread.detach();
    }
}

static void handle_connection(net_raii::TcpConnection&& conn, WriteFn* write) {
    bool has_disconnected = false;
    do {
        std::string msg = conn.recv_with_len(&has_disconnected);

        if (msg.length() > 0) {
            cout_safe("Message: ", msg, "\n");
            (*write)(msg);
        }
    } while(!has_disconnected);

    cout_safe("Connection ended.\n");
}


// Utilities
static void write_to_file_safe(const std::string& message, std::mutex& file_mutex, std::ofstream& log_file) {
    std::lock_guard<std::mutex> lock(file_mutex);
    if (log_file) {
        log_file << message << std::endl;
    }
}