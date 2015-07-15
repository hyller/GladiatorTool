#include "CppUTest/CommandLineTestRunner.h"

IMPORT_TEST_GROUP( TestSemVer);
IMPORT_TEST_GROUP( TestParse);
IMPORT_TEST_GROUP( TestUtils);

int main(int ac, char** av)
{
	return CommandLineTestRunner::RunAllTests(ac, av);
}


