#include "Logger.h"

using namespace Logger;

struct Streamable
{};

std::ostream& operator<<(std::ostream& os, const Streamable& /*unused*/)
{
    return os << "Streamable";
}

struct NonStreamable
{};

int main(int /*unused*/, const char** /*unused*/)
{
    setMinimumLogLevel(LogLevel::debug);

    debug("Debug level\n");
    info("Info level\n");
    warn("Warn level\n");
    error("Error level\n");
    critical("Critical level\n");
    fatal("fatal level\n");

    Streamable s;
    debug(s, '\n');

    info(NonStreamable{}, '\n');
    critical(Streamable{}, '\n');

    const NonStreamable c_n;
    volatile NonStreamable v_n;
    const volatile NonStreamable cv_n;

    const volatile NonStreamable& ref_cv_n = cv_n;

    info(c_n, "\n", v_n, "\n", cv_n, '\n', ref_cv_n, '\n');

    return 0;
}