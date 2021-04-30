cmake_minimum_required(VERSION 3.14)

project(RaychelCPU_test VERSION 0.0.1)

#find required libraries                TODO: add rest of the libraries

include(FetchContent)

FetchContent_Declare(GSL
    GIT_REPOSITORY "https://github.com/microsoft/GSL"
    GIT_TAG "v3.1.0"
)

FetchContent_MakeAvailable(GSL)

FetchContent_Declare(PNGPP
    GIT_REPOSITORY "https://github.com/usagi/pngpp"
)

FetchContent_MakeAvailable(PNGPP)

find_library(NCURSES ncurses curses)

if(NCURSES-NOTFOUND)
    message(STATUS "unable to find ncurses library, using fallback (no colors)")
    add_compile_definitions(RAYCHEL_USE_NCURSES_FALLBACK)

    set(NCURSES "")
endif()

#set all sources for the main testing file

set(RAYCHEL_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src/Raychel)

set(SOURCES 
    ${RAYCHEL_SOURCE_DIR}/Engine/Objects/Interface.cpp
    ${RAYCHEL_SOURCE_DIR}/Engine/Objects/sdObjects.cpp
    ${RAYCHEL_SOURCE_DIR}/Engine/Rendering/Pipeline/Shading.cpp
    ${RAYCHEL_SOURCE_DIR}/Engine/Rendering/Pipeline/RaymarchMath.cpp
    ${RAYCHEL_SOURCE_DIR}/Engine/Rendering/Renderer.cpp
    ${RAYCHEL_SOURCE_DIR}/Engine/Interface/Camera.cpp
    ${RAYCHEL_SOURCE_DIR}/Types.cpp
    ${RAYCHEL_SOURCE_DIR}/Engine/Rendering/RenderTarget/ImageTarget.cpp
    ${RAYCHEL_SOURCE_DIR}/Engine/Rendering/RenderTarget/AsciiTarget.cpp
    ${RAYCHEL_SOURCE_DIR}/Engine/Materials/Interface.cpp
    ${RAYCHEL_SOURCE_DIR}/Engine/Materials/Materials.cpp
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
    tbb                         #this might be bad
    png
    ${NCURSES}
    GSL
    INTERFACE PNGPP
)

#build time support for the sanitizers

if(${USE_ASAN})
    message(STATUS "Enabled ASAN support")
    target_compile_options(RaychelCPU_test PUBLIC -fsanitize=address -fno-omit-frame-pointer)
    target_link_options(RaychelCPU_test PUBLIC -fsanitize=address)
endif()

if(${USE_UBSAN})
    message(STATUS "EnabledUbSAN support")
    target_compile_options(RaychelCPU_test PUBLIC -fsanitize=undefined -fno-sanitize-recover -fno-omit-frame-pointer)
    target_link_options(RaychelCPU_test PUBLIC -fsanitize=undefined)
endif()

#general compiler flags

if(${MSVC})
    target_compile_options(RaychelCPU_test PUBLIC /W4 /wd4068)
else()
    target_compile_options(RaychelCPU_test PUBLIC -Wpedantic -Wall -Wextra -Wshadow -Wno-unknown-pragmas)
endif()

target_compile_features(RaychelCPU_test PUBLIC cxx_std_17)