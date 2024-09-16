#pragma once

#include <string>

namespace net_raii {

/// RAII Wrapper of linux file descriptor 
class FileDescriptor {
public:
    FileDescriptor();
    FileDescriptor(int fd);
    ~FileDescriptor();

    bool is_init() const;
    int get_file_descriptor() const;
    int take_descriptor_ownership();

    // Non-copyable
    FileDescriptor(const FileDescriptor&) = delete;
    FileDescriptor& operator=(const FileDescriptor&) = delete;

    // Movable
    FileDescriptor(FileDescriptor&& move_from);
    FileDescriptor& operator=(FileDescriptor&& move_from);


    // Sends: first 4 bytes of message byte length, then the message itself 
    void send_with_len(const std::string& message);
    std::string recv_with_len(bool* out_has_disconnected = nullptr);

protected:
    int m_file_descriptor;
};


} // namespace net_raii