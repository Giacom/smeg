#include "log.hpp"

#include <iostream>

namespace smeg {
    void Log(const char* message) {
        std::cout << message;
    }

    void Log(const std::string& message) {
        Log(message.c_str());
    }

    void LogLn(const char* message) {
        std::cout << message << "\n";
    }
    
    void LogLn(const std::string& message) {
        LogLn(message.c_str());
    }
}