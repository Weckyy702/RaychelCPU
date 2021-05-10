cmake_minimum_required(VERSION 3.14)

project(RaychelCPU VERSION 0.0.1)

option(USE_ASAN "If ASAN (AddressSanitizer) should be used" OFF)
option(USE_UBSAN "If UBSAN (UndefinedBehavourSanitizer) should be used. Has no effect on Windows" OFF)
option(USE_RAYCHEL_DEBUG "If specific debug only features of the engine should be enabled even in Release builds" ON)

if(${USE_RAYCHEL_DEBUG})

    add_compile_definitions(RAYCHEL_DEBUG)

endif()

add_subdirectory(RaychelLogger)

add_subdirectory(RaychelEngine)