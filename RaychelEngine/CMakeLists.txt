cmake_minimum_required(VERSION 3.10)

project(RaychelCPU_test)

add_executable(main src/test/main.cpp)

target_link_libraries(RaychelCPU_test PRIVATE
    RaychelLogger
)

target_compile_features(RaychelCPU_test PUBLIC cxx_std_17)