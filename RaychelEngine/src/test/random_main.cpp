#include <iostream>
#include <string>
#include <random>
#include "Logger.h"

#define RAYCHEL_NO_GSL

#include "Raychel/Misc/RNG/BufferedRNG.h"

using namespace Raychel;

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    const std::size_t test_count = 1'000'000;

    std::random_device rd{};
    std::ranlux48 rng{};

    std::uniform_real_distribution<float> distr_f{0, 1};
    std::uniform_int_distribution<int> distr_i{-5, 5};

    BufferedRNG<float> rng_f{1'000};
    BufferedRNG<int> rng_i{1'000};

    Logger::startTimer("BufferedRNG");
    for(size_t i = 0; i < test_count; i++) {
        [[maybe_unused]] volatile auto a = rng_f();
        [[maybe_unused]] volatile auto b = rng_i();
    }
    Logger::logDuration("BufferedRNG");

    Logger::startTimer("std::random");
    for(size_t i = 0; i < test_count; i++) {
        [[maybe_unused]] volatile auto a = distr_f(rng);
        [[maybe_unused]] volatile auto b = distr_i(rng);
    }
    Logger::logDuration("std::random");
}