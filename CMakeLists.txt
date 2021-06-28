cmake_minimum_required(VERSION 3.14)

project(RaychelCPU VERSION 0.0.1)

option(USE_ASAN "If ASAN (AddressSanitizer) should be used" ON)
option(USE_UBSAN "If UBSAN (UndefinedBehavourSanitizer) should be used. Has no effect on Windows" ON)
option(USE_RAYCHEL_DEBUG "If specific debug only features of the engine should be enabled even in Release builds" ON)
option(RAYCHEL_DO_TESTING "Enable Unit testing" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

if(${USE_RAYCHEL_DEBUG})

    add_compile_definitions(RAYCHEL_DEBUG)

endif()

if(${RAYCHEL_DO_TESTING})
    include(CTest)
endif()

add_subdirectory(RaychelLogger)
add_subdirectory(RaychelEngine)