#include <server/parsing.hpp>

#include <iostream>

Params parse_input(int argc, const char* const* argv, bool& out_error) {
    if (argc != 2) {
        std::cerr << "Incorrect input args" << std::endl;
        out_error = true;
        return Params { 
            .port = 0 
        };
    }

    Params result { .port = 0 };
    try {
        result.port = std::stoi(argv[1]);
    } 
    catch (const std::invalid_argument& e) {
        out_error = true;
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    }
    catch (const std::out_of_range& e) {
        out_error = true;
        std::cerr << "Out of range exception: " << e.what() << std::endl;
    }

    return result;
}