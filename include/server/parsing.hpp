#pragma once

#include <string>

struct Params {
    int port;
};
Params parse_input(int argc, const char* const* argv, bool& out_error);