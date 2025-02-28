#pragma once
#include <iostream>
#include <thread>
#include "log.h"

class Program {
public:
    using error_t = int;

    Program() noexcept;

    error_t start(int argc,char* argv[]);

    bool isValidArgs(int argc,char* argv[]);
    
    bool isValidImportanceLevel(const std::string& arg_str);
private:

    std::thread th;
    std::string logName;
    loglib::importanceLevel defaultLevel;
    
};
