#pragma once

#include <string>

namespace smeg {
    void Log(const char* message);
    void Log(const std::string& message);
    
    void LogLn(const char* message);
    void LogLn(const std::string& message);
}