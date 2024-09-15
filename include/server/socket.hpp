#pragma once

#include <netinet/in.h>

namespace server {

/// RAII Wrapper of sys/socket.h 
class Ipv4TcpSocket {
public:
    Ipv4TcpSocket();
    static Ipv4TcpSocket create_socket();

    ~Ipv4TcpSocket();

    bool is_init() const;
    int get_file_descriptor() const;

    // Non-copyable
    Ipv4TcpSocket(const Ipv4TcpSocket&) = delete;
    Ipv4TcpSocket& operator=(const Ipv4TcpSocket&) = delete;

    // Movable
    Ipv4TcpSocket(Ipv4TcpSocket&& move_from);
    Ipv4TcpSocket& operator=(Ipv4TcpSocket&& move_from);

    void bind_addr(in_addr_t address, in_port_t port);

private:
    int m_socket_fd;
};


} // namespace server