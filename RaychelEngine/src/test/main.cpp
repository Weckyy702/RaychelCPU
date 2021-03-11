#include "CMakeSettings.h"
#include "Logger.h"


int main(int argc, const char** argv)
{
	Logger::disableColor();

	Logger::log("Hello, World!\n");

    return 0;
}
