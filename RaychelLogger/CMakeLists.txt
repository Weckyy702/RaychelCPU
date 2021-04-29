cmake_minimum_required(VERSION 3.14)

project(RaychelLogger)

add_library(${PROJECT_NAME} STATIC src/Logger.cpp)

target_include_directories( ${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

add_executable(RaychelLogger_test src/tests/main.cpp)

target_include_directories(RaychelLogger_test PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(RaychelLogger_test PUBLIC
    RaychelLogger
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_compile_features(RaychelLogger_test PUBLIC cxx_std_17)