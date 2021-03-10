cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

project(RaychelCPU VERSION 0.0.1)

configure_file(include/CMakeSettings.h.in include/CMakeSettings.h)

add_executable(RaychelCPU src/test/main.cpp)

target_include_directories(RaychelCPU PUBLIC
					       "${PROJECT_BINARY_DIR}"
						   "${PROJECT_BINARY_DIR}/include"
					       )
