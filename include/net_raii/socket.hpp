#pragma once
#include <netinet/in.h>
#include <sys/socket.h>

#include <net_raii/file_descriptor.hpp>
#include <net_raii/connection.hpp>


namespace net_raii {

/// RAII Wrapper of sys/socket.h 
class TcpSocket : public FileDescriptor {
public:
    TcpSocket();
    TcpSocket(sa_family_t net_family);

    void bind_addr(in_addr_t address, in_port_t port);
    void allow_listen();

    TcpConnection accept_connection();

protected:
    sa_family_t m_net_family;
};


} // namespace net_raii