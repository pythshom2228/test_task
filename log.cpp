#include "log.h"
#include <iostream>
#include <ctime>

using namespace loglib;

Log::Log(const std::string& fileName, importanceLevel defaultLevel) noexcept : 
    _fileName(fileName), _defaultLevel(defaultLevel)  {
        _file.open(_fileName,std::ios::app);
        _file.close();
}


void Log::changeDefaultLevel(importanceLevel defaultLevel) {
    this->_defaultLevel = defaultLevel;    
}

const std::string& Log::getCurrentMessage() const {
    return _currentMessage;
}

bool Log::isInputValid(const std::string& inputText,const std::string& inputLevel) {
    if(inputText.empty()) {
        std::cout << "Error: Empty messages are not allowed" << "\n";
        return false;
    }
    
    if(!inputLevel.empty()) {
        const char firstChar = inputLevel[0];
        importanceLevel level = static_cast<importanceLevel>(firstChar - 48); // convertion from char to int
 
        if(!(level >= importanceLevel::LOW && level <= importanceLevel::HIGH)) {
            std::cout << "Error: Incorrect importanceLevel" << "\n";
            return false;
        }

        if(level < _defaultLevel) return false;
    }
    
    std::size_t quotes_pos[2] = {
        inputText.find("\""),
        inputText.rfind("\"")
    };

    if((quotes_pos[0] == std::string::npos) || (quotes_pos[1] == std::string::npos) || quotes_pos[0] == quotes_pos[1]) {
        std::cout << "Error: Quotes must be used" << "\n";
        return false;
    }
     

    return true;
}

void Log::saveMessage() {
    _file.open(_fileName,std::ios::app);

    if(!_currentMessage.empty())
        _file << _currentMessage.c_str();

    _file.close();
}


std::istream& loglib::operator>>(std::istream& in, Log& log) {
    log._currentMessage.clear();

    std::string inputLevel;
    std::cout << "Set importance Level: ";
    std::getline(in, inputLevel);
    std::cout << "\n";

    std::string inputText;
    std::cout << "Message to write to log: ";
    std::getline(in,inputText);
    std::cout << "\n"; 

    if(!log.isInputValid(inputText,inputLevel)) return in;

    std::size_t quotes_pos[2] = {
        inputText.find("\""),
        inputText.rfind("\"")
    };


    importanceLevel level = log._defaultLevel;
    if(!inputLevel.empty()) {
        const char firstChar = inputLevel[0];
        level = static_cast<importanceLevel>(firstChar-48); // convertion from char to int
    }
    std::string text = std::string(inputText.begin() + quotes_pos[0], inputText.begin() + (quotes_pos[1]+1)); 
    std::time_t timePoint = std::time(nullptr);



    switch(level) {
        case importanceLevel::LOW:
            log._currentMessage += "LOW";
            break;

        case importanceLevel::MID:
             log._currentMessage += "MID";
             break;

        case importanceLevel::HIGH:
             log._currentMessage += "HIGH";
             break;
    }

    log._currentMessage += "\t";
    log._currentMessage += text; 

    log._currentMessage += " ";
    log._currentMessage += std::asctime(std::localtime(&timePoint));
 
    return in;
}
