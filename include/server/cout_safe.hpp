#pragma once

#include <ostream>
#include <iostream>
#include <sstream>

template<typename Arg>
static void args_to_stream(std::ostream& os, const Arg& arg) {
    os << arg;
}

template<typename Arg, typename... Rest>
static void args_to_stream(std::ostream& os, const Arg& arg, const Rest&... rest) {
    os << arg;
    args_to_stream(os, rest...);
}

template<typename... T>
static void cout_safe(const T&... args) {
    std::stringstream ss;
    args_to_stream(ss, args...);
    std::cout << ss.str();
}
