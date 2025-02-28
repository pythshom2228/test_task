#pragma once
#include <fstream>
#include <string>

namespace loglib {

    enum class importanceLevel {
        LOW = 0,
        MID,
        HIGH
    };


    class Log {
    public:
        
        explicit Log(const std::string& fileName, importanceLevel defaultLevel) noexcept;

        void changeDefaultLevel(importanceLevel defaultLevel); 

        void saveMessage();

        const std::string& getCurrentMessage() const;

        bool isInputValid(const std::string& inputText,const std::string& inputLevel);

        friend std::istream& operator>>(std::istream& in, Log& log);

    private:
        std::string _fileName;
        std::string _currentMessage;
        std::ofstream _file; 
        importanceLevel _defaultLevel;
    };

    std::istream& operator>>(std::istream& in, Log& log);

}
