cmake_minimum_required(VERSION 3.10)

project(RaychelLogger)

add_library(${PROJECT_NAME} STATIC src/Logger.cpp)

add_executable(RaychelLogger_test src/tests/main.cpp)

target_include_directories( ${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_include_directories(RaychelLogger_test PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(RaychelLogger_test PUBLIC
    RaychelLogger
)

target_compile_features(RaychelLogger PUBLIC cxx_std_17)
target_compile_features(RaychelLogger_test PUBLIC cxx_std_17)