#include "CppUTest/CommandLineTestRunner.h"
#include "Scripts/TestAscii.h"

int main(int ac, char** av)
{
	return CommandLineTestRunner::RunAllTests(ac, av);
}


