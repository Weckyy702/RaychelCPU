cmake_minimum_required(VERSION 3.10)

project(RaychelLogger)

add_library(RaychelLogger STATIC src/Logger.cpp)

target_include_directories( ${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_compile_features(RaychelLogger PUBLIC cxx_std_17)