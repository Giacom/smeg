#include "log.hpp"

#include <iostream> // Only place allowed to have this header because it increases compile time so much

namespace smeg {

    const char* InfoPrefix = "\033[32mINFO:\033[0m ";
    const char* ErrorPrefix = "\033[31mERROR:\033[0m ";

    void Log(const std::string& message) {
        std::cout << InfoPrefix << message << "\n";
    }

    void LogError(const std::string& message) {
        std::cout << ErrorPrefix << message << "\n";
    }
}