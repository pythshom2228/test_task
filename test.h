#include "log.h"
#include "program.h"
#include <cassert>


struct Test {
    Test() = delete;

    static void startTests();

private:
    static void startLoglibTests();
    static void startProgramTests();

    static void testLogisInputValid();

    static void testProgramisValidArgs();
    static void testProgramisValidImportanceLevel();

};
