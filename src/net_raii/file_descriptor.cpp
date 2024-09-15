#include <net_raii/file_descriptor.hpp>
#include <unistd.h>

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


} // namespace net_raii