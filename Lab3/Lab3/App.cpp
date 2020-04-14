#include <iostream>

#include "TestScurt.h"
#include "TestExtins.h"

#include <crtdbg.h>

int main() {
    {
        testAll();
        testAllExtins();
        std::cout << "Finished LI Tests!" << std::endl;
    }
    _CrtDumpMemoryLeaks();
    return 0;
}