cmake_minimum_required(VERSION 3.10)

project(RaychelCPU VERSION 0.0.1)

option(USE_ASAN "If ASAN (AddressSanitizer) should be used" OFF)
option(USE_UBSAN "If UBSAN (UndefinedBehavourSanitizer) should be used" OFF)

add_subdirectory(RaychelLogger)

add_subdirectory(RaychelEngine)