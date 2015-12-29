#include "CppUTest/CommandLineTestRunner.h"
#include "TestAscii.h"

int main(int ac, char** av)
{
	return CommandLineTestRunner::RunAllTests(ac, av);
}


