#include "Logger.h"

using namespace Logger;

int main(int argc, char** argv)
{
    setMinimumLogLevel(LogLevel::debug);
    debug("Debug level\n");
    info("Info level\n");
    warn("Warn level\n");
    error("Error level\n");
    critical("Critical level\n");
    fatal("fatal level\n");
}