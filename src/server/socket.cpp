#include <server/socket.hpp>

#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

namespace server {

/// RAII Wrapper of sys/socket.h 
Ipv4TcpSocket::Ipv4TcpSocket() 
    : m_socket_fd(-1)
{}

Ipv4TcpSocket Ipv4TcpSocket::create_socket() {
    Ipv4TcpSocket s;

    s.m_socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (s.m_socket_fd == -1)
        throw new std::runtime_error("Failed to create a socket.");

    return s;
}

bool Ipv4TcpSocket::is_init() const {
    return m_socket_fd != -1;
}

int Ipv4TcpSocket::get_file_descriptor() const {
    return m_socket_fd;
}

Ipv4TcpSocket::~Ipv4TcpSocket() {
    if (m_socket_fd != -1)
        close(m_socket_fd);
}

Ipv4TcpSocket::Ipv4TcpSocket(Ipv4TcpSocket&& move_from) 
    : m_socket_fd(move_from.m_socket_fd)
{
    move_from.m_socket_fd = -1;
}

Ipv4TcpSocket& Ipv4TcpSocket::operator=(Ipv4TcpSocket&& move_from) {
    if (this != &move_from) {
        m_socket_fd = move_from.m_socket_fd;
        move_from.m_socket_fd = -1;
    }
    return *this;
}

void Ipv4TcpSocket::bind_addr(in_addr_t address, in_port_t port) {
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family      = AF_INET; // IPv4
    server_addr.sin_addr.s_addr = address;   
    server_addr.sin_port        = port;

    int bind_result = bind(m_socket_fd, (struct sockaddr*) &server_addr, sizeof(server_addr));

    if (bind_result == -1)
        throw std::runtime_error("Failed to bind to address");
}

} // namespace server