cmake_minimum_required(VERSION 3.10)

project(socket_pinger VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # For VSCode clang extension integraion

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")



add_library(net_raii STATIC
    src/net_raii/socket.cpp
    src/net_raii/file_descriptor.cpp
    src/net_raii/connection.cpp
)
target_include_directories(net_raii PUBLIC include/)

add_executable(server
    src/server/main.cpp
)
target_include_directories(server PUBLIC include/)
target_link_libraries(server PUBLIC net_raii)

add_executable(client
    src/client/main.cpp
)
target_include_directories(client PUBLIC include/)
target_link_libraries(client PUBLIC net_raii)