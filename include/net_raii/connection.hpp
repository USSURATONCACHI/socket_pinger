#pragma once

#include <net_raii/file_descriptor.hpp>
#include <sys/socket.h>

namespace net_raii {

/// RAII Wrapper of sys/socket.h TCP connection
class TcpConnection : public FileDescriptor {
public:
    using FileDescriptor::FileDescriptor; // using FileDescriptor constructors
};


} // namespace net_raii