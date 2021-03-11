cmake_minimum_required(VERSION 3.10)

project(RaychelCPU_test VERSION 0.0.1)

add_executable(RaychelCPU_test src/test/InheritanceVsTypeDeletion.cpp)

configure_file(${PROJECT_SOURCE_DIR}/include/CMakeSettings.h.in
${PROJECT_SOURCE_DIR}/include/CMakeSettings.h)

target_include_directories(RaychelCPU_test PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(RaychelCPU_test PRIVATE
    RaychelLogger
)

target_compile_features(RaychelCPU_test PUBLIC cxx_std_17)