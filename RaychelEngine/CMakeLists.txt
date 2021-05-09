cmake_minimum_required(VERSION 3.14)

project(RaychelCPU_test VERSION 0.0.1)

#find required libraries, download them if necessay
#TODO: add rest of the libraries

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

include(FetchContent)

find_file(GSL_MAIN_INCLUDE "gsl/gsl")
if(NOT GSL_MAIN_INCLUDE)

    message(STATUS "Could not find a local installation of gsl, downloading one off github...")

    FetchContent_Declare(GSL
        GIT_REPOSITORY "https://github.com/microsoft/GSL"
        GIT_TAG "v3.1.0"
    )

    FetchContent_MakeAvailable(GSL)

    set(LINK_GSL true)
else()
    set(LINK_GSL false)
endif() 



find_library(LIB_PNG png)
if(NOT LIB_PNG)

    message(STATUS "Could not find a local installation of libpng, downloading one off github...")

    FetchContent_Declare(libpng
        GIT_REPOSITORY "https://github.com/glennrp/libpng"
        GIT_TAG "v1.6.35"
    )

    FetchContent_Populate(libpng)

    include_directories(SYSTEM "${libpng_SOURCE_DIR}")

    file(READ  "${libpng_SOURCE_DIR}/scripts/pnglibconf.h.prebuilt" PNGLIBCONF_H_CONTENT)
    file(WRITE "${libpng_SOURCE_DIR}/pnglibconf.h" ${PNGLIBCONF_H_CONTENT})

    add_subdirectory(${libpng_SOURCE_DIR} ${libpng_BINARY_DIR})

    #file(COPY )
endif()



find_file(PNGPP_MAIN_INCLUDE "png++/png.hpp")
if(NOT PNGPP_MAIN_INCLUDE)

    message(STATUS "Could not find a local installation of png++, downloading one off github...")

    FetchContent_Declare(pngpp
        GIT_REPOSITORY "https://github.com/usagi/pngpp"
    )

    FetchContent_GetProperties(pngpp)
    if(NOT pngpp_POPULATED)
        FetchContent_Populate(pngpp)
        file(GLOB PNGPP_HEADERS "${pngpp_SOURCE_DIR}/*.hpp")
        file(REMOVE_RECURSE "${pngpp_SOURCE_DIR}/include/png++")
        file(COPY ${PNGPP_HEADERS} DESTINATION "${pngpp_SOURCE_DIR}/include/png++/")
    endif()
endif()



find_library(LIB_NCURSES ncurses curses)

if(NOT LIB_NCURSES)
    message(STATUS "unable to find ncurses library, using fallback (no colors)")
    add_compile_definitions(RAYCHEL_USE_NCURSES_FALLBACK)

    set(LIB_NCURSES "")
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



#this assumes that zlib has been installed via zlib.install at https://github.com/horta/zlib.install
if(WIN32)
    find_package(ZLIB REQUIRED)
    set(ZLIB_LIBRARY_DIR ${ZLIB_LIBRARY})

    string(REPLACE "lib/zlib.lib" "bin/zlib.dll" ZLIB_DLL_LOCATION ${ZLIB_LIBRARY_DIR})

    file(COPY ${ZLIB_DLL_LOCATION} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

    add_custom_command(TARGET RaychelCPU_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/zlib.dll $<TARGET_FILE_DIR:RaychelCPU_test>    
    )   
endif()



#set the needed include directories
configure_file( ${PROJECT_SOURCE_DIR}/include/CMakeSettings.h.in
                ${PROJECT_SOURCE_DIR}/include/CMakeSettings.h
)

target_include_directories(RaychelCPU_test PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${pngpp_SOURCE_DIR}/include
)

#Set compiler flags
#build time support for sanitizers
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

#General compiler flags
if(${MSVC})
    target_compile_options(RaychelCPU_test PUBLIC /W4 /wd4068)
else()
    target_compile_options(RaychelCPU_test PUBLIC -Wall -Wextra -Wshadow -Wno-unknown-pragmas)
endif()

include(CheckIPOSupported)
check_ipo_supported(RESULT IPO_SUPPORTED OUTPUT ERROR)

if(IPO_SUPPORTED)
    message(STATUS "IPO / LTO enabled")
    set_target_properties(RaychelCPU_test PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION true
    )
else()
    message(STATUS "IPO / LTO disabled ${ERROR}")
endif()

#Gimme that C++17 goodness
target_compile_features(RaychelCPU_test PUBLIC cxx_std_17)



#link the correct libraries
target_link_libraries(RaychelCPU_test PRIVATE
    RaychelLogger
    png
    ${LIB_NCURSES}
)

if(LINK_GSL)
    target_link_libraries(RaychelCPU_test PRIVATE
        GSL
    )
endif()

if(${CMAKE_CXX_COMPILER} MATCHES ".*/gcc.*")
    target_link_libraries(RaychelCPU_test PUBLIC
        tbb
    )
endif()