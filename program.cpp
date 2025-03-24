#include "program.h"
#include <chrono>
#include <atomic>
#include <mutex>

using namespace loglib;

Program::Program() noexcept {}


bool Program::isValidArgs(int argc, char* argv[]) {    
    if(argc > 3 || argc < 2) {
        std::cout << "Error: Incorrect input number, try again" << "\n";
        return false; 
    }
    if(argc == 2) {
        std::cout << "Error: Default importance level must be set" << "\n";
        return false;
    }
    
    if(!isValidImportanceLevel(std::string(argv[2]))) return false;
    
    return true;
 }

bool Program::isValidImportanceLevel(const std::string& arg_str) {
    importanceLevel arg;
    try {
        arg = static_cast<importanceLevel>(std::stoi(arg_str));
    } catch(...) {
        std::cout << "Error: Incorrect importance level" << "\n";
        return false;
    }
  
    if(!(arg >= importanceLevel::LOW && arg <= importanceLevel::HIGH)) {
        std::cout << "Error: Invalid importance level" << "\n";
        return false;
    }
    return true;
}


error_t Program::start(int argc, char* argv[]) {
    if(!isValidArgs(argc, argv)) return EXIT_FAILURE;

    logName = argv[1];

    std::string arg_str = argv[2];
    defaultLevel = static_cast<importanceLevel>(std::stoi(arg_str));

    Log log {logName + std::string(".txt"), defaultLevel};
    

    std::atomic<bool> running(true);

    std::atomic<bool> userInputted(false);
    std::mutex logMutex;

    auto save = [&]() mutable {
        while (running.load()) {
            if(userInputted.exchange(false)) {
                std::lock_guard<std::mutex> lock(logMutex);
                log.saveMessage();
            }
        }
    };


    this->th = std::thread(save);

    while(running) {
        {
            std::lock_guard<std::mutex> lock(logMutex);
            std::cin >> log; 
        }
    
        userInputted.store(true);

        std::cout << "\n";
    }
    th.join();
    return EXIT_SUCCESS;
}
