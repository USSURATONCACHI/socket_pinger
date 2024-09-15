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


add_executable(server
    src/server/main.cpp
    src/server/socket.cpp
    src/server/file_descriptor.cpp
)
target_include_directories(server PUBLIC include/)