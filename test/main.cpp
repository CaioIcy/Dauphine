#include "CppUTest/CommandLineTestRunner.h"

#include "unit/test_Math.cpp"

int main(int argc, char** argv) {
    return CommandLineTestRunner::RunAllTests(argc, argv);
}
