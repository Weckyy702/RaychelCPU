cmake_minimum_required(VERSION 3.14)

project(RaychelLogger)

add_library(${PROJECT_NAME} SHARED src/Logger.cpp)

target_compile_definitions(${PROJECT_NAME} PUBLIC
    RAYCHELLOGGER_EXPORTS
)

target_include_directories( ${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)