cmake_minimum_required(VERSION 3.14)

project(RaychelCPU_test LANGUAGES CXX VERSION 0.0.1)

include(FindRequiredLibraries.cmake)

#set all sources for the main testing file

set(RAYCHEL_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src/Raychel)
set(RAYCHEL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

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
    ${RAYCHEL_SOURCE_DIR}/Engine/Interface/Scene.cpp
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
configure_file( ${RAYCHEL_INCLUDE_DIR}/CMakeSettings.h.in
                ${RAYCHEL_INCLUDE_DIR}/CMakeSettings.h
)

target_include_directories(RaychelCPU_test PUBLIC
    ${RAYCHEL_INCLUDE_DIR}
    ${pngpp_SOURCE_DIR}/include
)

#Set compiler flags
#build time support for sanitizers
if(${USE_ASAN})
    message(STATUS "Enabled ASAN support")

    list(APPEND RAYCHEL_COMPILER_FLAGS
        -fsanitize=address
    )

    if(NOT MSVC)
        target_compile_options(RaychelCPU_test PUBLIC -fno-omit-frame-pointer)
        target_link_options(RaychelCPU_test PUBLIC -fsanitize=address)
    else()
        message(WARNING "It looks like you're using MSVC. On Visual Studio, please head into RaychelCPU properties and tick 'Enable Address Sanitizer'")
    endif()

endif()

#MSVC does not support UBSAN :(
if(${USE_UBSAN} AND NOT MSVC)
    message(STATUS "EnabledUbSAN support")

    list(APPEND RAYCHEL_COMPILER_FLAGS
        -fsanitize=undefined
        -fsanitize=float-divide-by-zero
        -fno-sanitize-recover
        -fno-omit-frame-pointer
    )
    target_link_options(RaychelCPU_test PUBLIC -fsanitize=undefined)
endif()

#General compiler flags
if(${MSVC})
    list(APPEND RAYCHEL_COMPILER_FLAGS
        /W4 
        /wd4068 #unknown pragma
    )
else()
    list(APPEND RAYCHEL_COMPILER_FLAGS
        -Wall
        -Wextra
        -Wshadow 
        -Wno-unknown-pragmas
    )
endif()

target_compile_options(RaychelCPU_test PUBLIC
    ${RAYCHEL_COMPILER_FLAGS}
)

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

if(NOT MSVC)
    target_link_libraries(RaychelCPU_test PUBLIC
        tbb
    )
endif()

#Unit tests
if(${RAYCHEL_DO_TESTING})
    add_subdirectory(src/test)
endif()