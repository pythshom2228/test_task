#include "test.h"
#define assertm(exp, msg) assert((void(msg), exp))
using namespace loglib;

void Test::startTests() {

    std::cout << "=============\t" << "TESTS STARTING" << "\t=============" << "\n";
    
    startLoglibTests();
    startProgramTests();

    std::cout << "=============\t" << "TESTS PASSED CORRECTLY" << "\t=============" << "\n";
}



void Test::startLoglibTests() {
    testLogisInputValid();
    std::cout << "Log tests: OK\n";
}

// Проверка валидации ввода
void Test::testLogisInputValid() {
    Log log("test_log.txt", importanceLevel::LOW);

    // Пустое сообщение
    assertm(log.isInputValid("", "1") == false, "Empty message should be invalid");

    // Некорректный уровень
    assertm(log.isInputValid("\"text\"", "a") == false, "Invalid level (non-digit)");
    assertm(log.isInputValid("\"text\"", "4") == false, "Invalid level (out of range)");

    // Уровень ниже дефолтного (дефолт MID)
    log.changeDefaultLevel(importanceLevel::MID);
    assertm(log.isInputValid("\"text\"", "0") == false, "Level < default should be invalid");

    // Нет кавычек
    assertm(log.isInputValid("text", "1") == false, "No quotes should be invalid");

    // Корректные данные
    assertm(log.isInputValid("\"valid text\"", "2") == true, "Valid input");
}





void Test::startProgramTests() {
    testProgramisValidArgs();
    testProgramisValidImportanceLevel();
    std::cout << "Program tests: OK\n";
}

// Проверка аргументов командной строки
void Test::testProgramisValidArgs() {
    Program program;
    const char* invalid1[] = {"./program", "file"}; // argc=2 (не хватает уровня)
    const char* valid[] = {"./program", "file", "1"};

    assertm(program.isValidArgs(2, const_cast<char**>(invalid1)) == false, "argc=2 should fail");
    assertm(program.isValidArgs(3, const_cast<char**>(valid)) == true, "Valid args should pass");
}

// Проверка уровня важности
void Test::testProgramisValidImportanceLevel() {
    Program program;
    assertm(program.isValidImportanceLevel("0") == true, "Valid level (0)");
    assertm(program.isValidImportanceLevel("3") == false, "Invalid level (3)");
    assertm(program.isValidImportanceLevel("abc") == false, "Non-integer level");
}



int main() {
    Test::startTests();
    return 0;
}