#include "CppUTest/CommandLineTestRunner.h"
#include <iostream>

int main(int ac, char** av)
{
	std::cout << "AI MEU DEUS\n";
    return CommandLineTestRunner::RunAllTests(ac, av);
}
