#pragma once

#include <server/file_descriptor.hpp>
#include <sys/socket.h>

namespace server {

/// RAII Wrapper of sys/socket.h TCP connection
class TcpConnection : FileDescriptor {
public:

};


} // namespace server