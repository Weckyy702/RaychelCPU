cmake_minimum_required(VERSION 3.14)

project(RaychelCPU VERSION 0.0.1)

option(USE_ASAN "If ASAN (AddressSanitizer) should be used" OFF)
option(USE_UBSAN "If UBSAN (UndefinedBehavourSanitizer) should be used" OFF)
option(USE_RAYCHEL_DEBUG "If specific debug only features of the engine should be enabled even in Release builds" ON)

if(${USE_RAYCHEL_DEBUG})

    add_compile_definitions(RAYCHEL_DEBUG)

endif()

include(CheckIPOSupported)

check_ipo_supported(RESULT IPO_SUPPORTED OUTPUT ERROR)

if(IPO_SUPPORTED)
    message(STATUS "IPO / LTO enabled")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
    message(STATUS "IPO / LTO disabled <${ERROR}>")
endif()

add_subdirectory(RaychelLogger)

add_subdirectory(RaychelEngine)