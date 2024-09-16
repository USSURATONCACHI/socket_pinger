#include <cerrno>
#include <cstdint>
#include <net_raii/file_descriptor.hpp>
#include <sys/types.h>
#include <unistd.h>

#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>

namespace net_raii {


FileDescriptor::FileDescriptor() 
    : m_file_descriptor(-1)
{}

FileDescriptor::FileDescriptor(int fd) 
    : m_file_descriptor(fd)
{}

bool FileDescriptor::is_init() const {
    return m_file_descriptor != -1;
}

int FileDescriptor::get_file_descriptor() const {
    return m_file_descriptor;
}

int FileDescriptor::take_descriptor_ownership() {
    int fd = m_file_descriptor;
    m_file_descriptor = -1;
    return fd;
}

FileDescriptor::~FileDescriptor() {
    if (m_file_descriptor != -1)
        close(m_file_descriptor);
}

FileDescriptor::FileDescriptor(FileDescriptor&& move_from) 
    : m_file_descriptor(move_from.m_file_descriptor)
{
    move_from.m_file_descriptor = -1;
}

FileDescriptor& FileDescriptor::operator=(FileDescriptor&& move_from) {
    if (this != &move_from) {
        m_file_descriptor = move_from.m_file_descriptor;
        move_from.m_file_descriptor = -1;
    }
    return *this;
}


    // Sends: first 4 bytes of message byte length, then the message itself 
    void send_with_len(const std::string& message);
    std::string recv_with_len(bool* out_has_disconnected = nullptr);

void FileDescriptor::send_with_len(const std::string& message) {
    uint32_t length = message.length();

    ::send(get_file_descriptor(), &length, sizeof(length), 0);
    ::send(get_file_descriptor(), message.c_str(), message.length(), 0);
}

std::string FileDescriptor::recv_with_len(bool* out_has_disconnected) {
    uint32_t length = 0;
    ssize_t bytes_read = ::read(get_file_descriptor(), &length, sizeof(length));

    if (bytes_read < 1) {
        (*out_has_disconnected) = true;
        return "";
    }

    char* buffer = new char[length];
    
    ssize_t total_bytes_read = 0;
    bool should_stop = false;
    do {
        ssize_t this_packet_read = ::read(get_file_descriptor(), buffer + total_bytes_read, length - total_bytes_read);

        if (this_packet_read < 1) {
            should_stop = true;
            (*out_has_disconnected) = true;
            this_packet_read = 0;
        }

        total_bytes_read += this_packet_read;
    } while(total_bytes_read < length && !should_stop);
    
    buffer[total_bytes_read] = '\0';
    
    std::string str(buffer);
    return str;
}


} // namespace net_raii