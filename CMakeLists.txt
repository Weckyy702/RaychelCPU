cmake_minimum_required(VERSION 3.14)

project(RaychelCPU VERSION 0.0.1)

option(USE_ASAN "If ASAN (AddressSanitizer) should be used" OFF)
option(USE_UBSAN "If UBSAN (UndefinedBehavourSanitizer) should be used. Has no effect on Windows" OFF)
option(USE_RAYCHEL_DEBUG "If specific debug only features of the engine should be enabled even in Release builds" ON)
option(RAYCHEL_DO_TESTING "Enable Unit testing" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

if(${USE_RAYCHEL_DEBUG})

    add_compile_definitions(RAYCHEL_DEBUG)

endif()

if(${RAYCHEL_DO_TESTING})
    include(CTest)
endif()

add_subdirectory(RaychelLogger)
add_subdirectory(RaychelEngine)