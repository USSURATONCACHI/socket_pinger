#include <net_raii/socket.hpp>

#include <netinet/in.h>
#include <stdexcept>
#include <cstring>
#include <vector>
#include <iostream>

#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <net_raii/connection.hpp>
#include <net_raii/file_descriptor.hpp>

namespace net_raii {

TcpSocket::TcpSocket() : 
    FileDescriptor(), 
    m_net_family(AF_INET)
{}

TcpSocket::TcpSocket(sa_family_t net_family) : 
    FileDescriptor(socket(net_family, SOCK_STREAM, 0)),
    m_net_family(net_family)
{
    if (get_file_descriptor() == -1)
        throw new std::runtime_error("Failed to create a socket.");
}

void TcpSocket::bind_addr(in_addr_t address, in_port_t port) {
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family      = m_net_family; // IPv4
    server_addr.sin_addr.s_addr = address;   
    server_addr.sin_port        = port;

    int bind_result = bind(get_file_descriptor(), (struct sockaddr*) &server_addr, sizeof(server_addr));

    if (bind_result == -1)
        throw std::runtime_error("Failed to bind to address.");
}

void TcpSocket::connect_to_addr(in_addr_t address, in_port_t port) {
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family      = m_net_family; // IPv4
    server_addr.sin_addr.s_addr = address;   
    server_addr.sin_port        = port;

    int connect_result = connect(get_file_descriptor(), (struct sockaddr*) &server_addr, sizeof(server_addr));

    if (connect_result == -1)
        throw std::runtime_error("Failed to connect to address.");
}


void TcpSocket::allow_listen() {
    int listen_result = listen(get_file_descriptor(), SOMAXCONN);
    if (listen_result == -1)
        throw std::runtime_error("Failed to listen on socket.");
}

TcpConnection TcpSocket::accept_connection() {
    int client_fd = accept(get_file_descriptor(), nullptr, nullptr);

    if (client_fd == -1)
        throw std::runtime_error("Failed to accept connection.");

    return TcpConnection(client_fd);
}

in_addr_t TcpSocket::address_from_text(const std::string& text) {
    in_addr_t addr = {0};

    if (inet_pton(AF_INET, text.c_str(), &addr) <= 0)
        throw std::runtime_error("Cannot convert text address to in_addr_t");
    
    return addr;
}

void TcpSocket::send(const std::string& message) {
    ::send(get_file_descriptor(), message.c_str(), message.length(), 0);
}
std::string TcpSocket::recv() {
    std::vector<char> result;

    size_t bytes_read;
    do {
        char buffer[1024];
        result.reserve(sizeof(buffer));
        bytes_read = ::read(m_file_descriptor, buffer, sizeof(buffer));

        result.insert(result.end(), buffer, buffer + bytes_read);
    } while (bytes_read > 0);

    std::string str(result.begin(), result.end());
    return str;
}

} // namespace net_raii