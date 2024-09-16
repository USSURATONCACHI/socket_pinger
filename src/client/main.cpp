#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>

#include <net_raii/socket.hpp>
#include <client/parsing.hpp>

#define SERVER_ADDRESS "127.0.0.1"

static void run_client(Params p);
static std::string get_current_time();

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

        std::string msg = "[" + get_current_time() + "] " + p.name;
        socket.send_with_len(msg);
        std::this_thread::sleep_for(std::chrono::microseconds(period_microsec));
    }
}

static std::string get_current_time() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_time_t);
    
    auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S") << ".";
    oss << std::setw(3) << std::setfill('0') << now_ms.count();

    return oss.str();
}