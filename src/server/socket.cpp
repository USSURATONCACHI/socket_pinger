#include "server/file_descriptor.hpp"
#include <server/socket.hpp>

#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

namespace server {

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

void TcpSocket::allow_listen() {
    int listen_result = listen(get_file_descriptor(), SOMAXCONN);
    if (listen_result == -1)
        throw std::runtime_error("Failed to listen on socket.");
}

} // namespace server