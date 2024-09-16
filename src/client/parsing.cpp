#include <client/parsing.hpp>

#include <iostream>

static double parse_double(const char* arg, bool& out_error);
static int parse_int(const char* arg, bool& out_error);


Params parse_input(int argc, const char* const* argv, bool& out_error) {
    if (argc != 4) { // name, port,  period
        std::cerr << "Incorrect input args" << std::endl;
        out_error = true;
        return Params();
    }

    Params result {
        .port = parse_int(argv[2], out_error),
        .name = std::string(argv[1]),
        .sending_period = parse_double(argv[3], out_error),
    };

    return result;
}

static int parse_int(const char* arg, bool& out_error) {
    int result = 0;
    try {
        result = std::stoi(arg);
    } 
    catch (const std::invalid_argument& e) {
        out_error = true;
        std::cerr << "Invalid argument '" << arg << "': " << e.what() << std::endl;
    }
    catch (const std::out_of_range& e) {
        out_error = true;
        std::cerr << "Out of range exception on '" << arg << "': " << e.what() << std::endl;
    }

    return result;
}

static double parse_double(const char* arg, bool& out_error) {
    double res = 1.0;
    try {
        res = std::stod(arg);
    } 
    catch (const std::exception& e) {
        out_error = true;
        std::cerr << "Invalid argument '" << arg << "': " << e.what() << std::endl;
    }
    return res;
}