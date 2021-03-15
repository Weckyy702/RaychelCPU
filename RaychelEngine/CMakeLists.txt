cmake_minimum_required(VERSION 3.10)

project(RaychelCPU_test VERSION 0.0.1)

set(RAYCHEL_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src/Raychel)

set(SOURCES 
    ${RAYCHEL_SOURCE_DIR}/Engine/Objects/Interface.cpp
    ${RAYCHEL_SOURCE_DIR}/Engine/Objects/sdObjects.cpp
    ${RAYCHEL_SOURCE_DIR}/Engine/Rendering/Pipeline/Shading.cpp
    ${RAYCHEL_SOURCE_DIR}/Engine/Rendering/Renderer.cpp
)

add_executable(RaychelCPU_test 
    ${PROJECT_SOURCE_DIR}/src/test/main.cpp
    ${SOURCES}
)

configure_file( ${PROJECT_SOURCE_DIR}/include/CMakeSettings.h.in
                ${PROJECT_SOURCE_DIR}/include/CMakeSettings.h
)

target_include_directories(RaychelCPU_test PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(RaychelCPU_test PRIVATE
    RaychelLogger
    tbb
)

target_compile_features(RaychelCPU_test PUBLIC cxx_std_17)