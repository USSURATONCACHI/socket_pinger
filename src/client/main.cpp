#include <cassert>
#include <chrono>
#include <exception>
#include <iostream>
#include <string>
#include <thread>

#include <net_raii/socket.hpp>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_ADDRESS "127.0.0.1"

struct Params {
    int port;
    std::string name;
    double sending_period;
};
static Params parse_input(int argc, const char* const* argv, bool& out_error);
static double parse_double(const char* arg, bool& out_error);
static int parse_int(const char* arg, bool& out_error);

static void run_client(Params p);

int main(int argc, char** argv) {
    bool had_error = false;
    Params p = parse_input(argc, argv, had_error);

    if (had_error) {
        std::cout << "Usage: " << argv[0] << " <client_name> <server_port> <sending_period>" << std::endl;
        return 1;
    }

    run_client(p);
    return 0;
}

static void run_client(Params p) {
    uint64_t period_microsec = (uint64_t)(p.sending_period * 1000.0 * 1000.0);

    net_raii::TcpSocket socket(AF_INET);
    std::cout << "Socket created" << std::endl;

    in_addr_t addr = socket.address_from_text(SERVER_ADDRESS);
    socket.connect_to_addr(addr, htons(p.port));
    std::cout << "Socket connected" << std::endl;

    while (true) {
        std::cout << "Sending (" << p.name << ")" << std::endl;

        socket.send_with_len(p.name);
        std::this_thread::sleep_for(std::chrono::microseconds(period_microsec));
    }
}


// --- Parsing
static Params parse_input(int argc, const char* const* argv, bool& out_error) {
    if (argc != 4) { // name, port,  period
        std::cerr << "Incorrect input args" << std::endl;
        out_error = true;
        return Params();
    }

    Params result {
        .port = parse_int(argv[2], out_error),
        .name = std::string(argv[1]),
        .sending_period = parse_double(argv[3], out_error),
    };

    return result;
}

static int parse_int(const char* arg, bool& out_error) {
    int result = 0;
    try {
        result = std::stoi(arg);
    } 
    catch (const std::invalid_argument& e) {
        out_error = true;
        std::cerr << "Invalid argument '" << arg << "': " << e.what() << std::endl;
    }
    catch (const std::out_of_range& e) {
        out_error = true;
        std::cerr << "Out of range exception on '" << arg << "': " << e.what() << std::endl;
    }

    return result;
}

static double parse_double(const char* arg, bool& out_error) {
    double res = 1.0;
    try {
        res = std::stod(arg);
    } 
    catch (const std::exception& e) {
        out_error = true;
        std::cerr << "Invalid argument '" << arg << "': " << e.what() << std::endl;
    }
    return res;
}