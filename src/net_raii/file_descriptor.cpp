#include <net_raii/file_descriptor.hpp>
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


void FileDescriptor::send(const std::string& message) {
    ::send(get_file_descriptor(), message.c_str(), message.length(), 0);
}
std::string FileDescriptor::recv() {
    std::vector<char> result;

    size_t bytes_read;
    do {
        char buffer[1024];
        result.reserve(sizeof(buffer));
        bytes_read = ::read(get_file_descriptor(), buffer, sizeof(buffer));

        result.insert(result.end(), buffer, buffer + bytes_read);
    } while (bytes_read > 0);

    std::string str(result.begin(), result.end());
    return str;
}


} // namespace net_raii