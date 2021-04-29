cmake_minimum_required(VERSION 3.14)

project(RaychelLogger)

add_library(${PROJECT_NAME} STATIC src/Logger.cpp)

target_include_directories( ${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)