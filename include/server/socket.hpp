#pragma once
#include <netinet/in.h>
#include <sys/socket.h>

#include <server/file_descriptor.hpp>
#include <server/connection.hpp>


namespace server {

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


} // namespace server