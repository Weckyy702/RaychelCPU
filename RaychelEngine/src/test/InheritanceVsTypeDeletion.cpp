#include "CMakeSettings.h"
#include "Logger.h"
#include "Raychel/Raychel.h"
#include "Raychel/Engine/Raymarchable/Interface.h"

using namespace Raychel;

using sd_t = _sdCallable;

struct sdSphere
{
	double eval(const vec3&) const
	{
		return 0.0;
	}
};

struct ISdObject
{
	virtual double eval(const vec3&)=0;
};

struct sdCube : public ISdObject
{
	double eval(const vec3&) override
	{
		return 0.0;
	}
};


int main(int argc, const char** argv)
{
	Logger::setMinimumLogLevel(Logger::LogLevel::debug);
	Logger::info("Testing Raychel Version ", RAYCHEL_VERSION_TAG, '\n');

	for(int i = 0; i < 10; i++) {

		sd_t obj1 = sdSphere{};

		auto label = Logger::startTimer("Type-deleted");

		for(uint64_t i = 0; i < 1'000'000'000; i++) {
			volatile double v = obj1.eval(vec3{});
		}

		Logger::logDuration(label);

		ISdObject* obj2 = new sdCube{};

		label = Logger::startTimer("Inheritance");

		for(uint64_t i = 0; i < 1'000'000'000; i++) {
			volatile double v = obj2->eval(vec3{});
		}

		Logger::logDuration(label);

		delete obj2;
	}

    return 0;
}
