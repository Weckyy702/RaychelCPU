cmake_minimum_required(VERSION 3.10)

project(RaychelCPU VERSION 0.0.1)

option(USE_ASAN "If ASAN (AddressSanitizer) should be used" OFF)
option(USE_UBSAN "If UBSAN (UndefinedBehavourSanitizer) should be used" OFF)
option(USE_RAYCHEL_DEBUG "If specific debug only features of the engine should be enabled even in Release builds" ON)

if(${USE_RAYCHEL_DEBUG})

    add_compile_definitions(-DRAYCHEL_DEBUG=1)

endif()

add_subdirectory(RaychelLogger)

add_subdirectory(RaychelEngine)