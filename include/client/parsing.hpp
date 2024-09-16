#pragma once

#include <string>

struct Params {
    int port;
    std::string name;
    double sending_period;
};
Params parse_input(int argc, const char* const* argv, bool& out_error);
