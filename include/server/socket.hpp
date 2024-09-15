#pragma once

#include <server/file_descriptor.hpp>
#include <netinet/in.h>
#include <sys/socket.h>

namespace server {

/// RAII Wrapper of sys/socket.h 
class TcpSocket : public FileDescriptor {
public:
    TcpSocket();
    TcpSocket(sa_family_t net_family);

    void bind_addr(in_addr_t address, in_port_t port);
    void allow_listen();

protected:
    sa_family_t m_net_family;
};


} // namespace server