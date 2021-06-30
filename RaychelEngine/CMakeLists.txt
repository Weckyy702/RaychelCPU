cmake_minimum_required(VERSION 3.14)

project(Raychel LANGUAGES CXX VERSION 0.0.1)

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
    ${RAYCHEL_SOURCE_DIR}/Engine/Rendering/RenderTarget/AsciiImpl.cpp
    ${RAYCHEL_SOURCE_DIR}/Engine/Materials/Interface.cpp
    ${RAYCHEL_SOURCE_DIR}/Engine/Materials/Materials.cpp
    ${RAYCHEL_SOURCE_DIR}/Engine/Interface/Scene.cpp
)

add_library(${PROJECT_NAME} SHARED
    ${SOURCES}
)

target_compile_definitions(${PROJECT_NAME} PUBLIC
    RAYCHEL_EXPORTS
)

#set the needed include directories
configure_file( ${RAYCHEL_INCLUDE_DIR}/CMakeSettings.h.in
                ${RAYCHEL_INCLUDE_DIR}/CMakeSettings.h
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${RAYCHEL_INCLUDE_DIR}
    ${pngpp_SOURCE_DIR}/include
)

set(RAYCHEL_COMPILER_FLAGS)

#Set compiler flags
#build time support for sanitizers
if(${USE_ASAN})
    message(STATUS "Enabled ASAN support")

    if(NOT MSVC)
        list(APPEND RAYCHEL_COMPILER_FLAGS
            -fsanitize=address
            -fno-omit-frame-pointer
        )
        list(APPEND RAYCHEL_LINKER_FLAGS
            -fsanitize=address
        )
    else()
        message(WARNING "It looks like you're using MSVC. On Visual Studio, please head into ${PROJECT_NAME} properties and tick 'Enable Address Sanitizer'")
    endif()

endif()

#MSVC does not support UBSAN :(
if(${USE_UBSAN} AND NOT MSVC)
    message(STATUS "Enabled UBSAN support")

    list(APPEND RAYCHEL_COMPILER_FLAGS
        -fsanitize=undefined
        -fsanitize=float-divide-by-zero
        -fno-sanitize-recover
        -fno-omit-frame-pointer
    )
    list(APPEND RAYCHEL_LINKER_FLAGS -fsanitize=undefined)
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
        -Wconversion
    )
endif()

target_compile_options(${PROJECT_NAME} PUBLIC
    ${RAYCHEL_COMPILER_FLAGS}
)

include(CheckIPOSupported)
check_ipo_supported(RESULT IPO_SUPPORTED OUTPUT ERROR)

if(IPO_SUPPORTED)
    message(STATUS "IPO / LTO enabled")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION true
    )
else()
    message(STATUS "IPO / LTO disabled ${ERROR}")
endif()

#Gimme that C++17 goodness
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)


#link the correct libraries
target_link_options(${PROJECT_NAME} PUBLIC
    ${RAYCHEL_LINKER_FLAGS}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC RaychelLogger
    PRIVATE png
    ${LIB_NCURSES}
)

if(LINK_GSL)
    target_link_libraries(${PROJECT_NAME} PUBLIC
        GSL
    )
endif()

if(NOT MSVC)
    target_link_libraries(${PROJECT_NAME} PUBLIC
        tbb
    )
endif()

#Unit tests
if(${RAYCHEL_DO_TESTING})
    add_subdirectory(src/test)
endif()

#needed if zlib is not pre installed on your system
if(RAYCHEL_MOVE_ZLIB_FILES)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/zlib.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )   
endif()