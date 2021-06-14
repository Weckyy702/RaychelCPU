#find required libraries, download them if necessay
#TODO: add rest of the libraries

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

    set(PNG_TESTS OFF) #we don't want libpng to make our tests noisy
    file(READ  "${libpng_SOURCE_DIR}/scripts/pnglibconf.h.prebuilt" PNGLIBCONF_H_CONTENT)
    file(WRITE "${libpng_SOURCE_DIR}/pnglibconf.h" ${PNGLIBCONF_H_CONTENT})

    add_subdirectory(${libpng_SOURCE_DIR} ${libpng_BINARY_DIR})
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


#Catch2 is only required if we build the unit tests
if(${RAYCHEL_DO_TESTING})

    find_package(Catch2 QUIET)

    if(NOT Catch2_FOUND)

        message(STATUS "Could not find a local installation of Catch2, downloading one off github...")

        FetchContent_Declare(CATCH_2
            GIT_REPOSITORY "https://github.com/catchorg/Catch2"
            GIT_TAG "v2.13.6"
        )

        FetchContent_MakeAvailable(CATCH_2)

        set(CATCH_2_EXTERNAL true)
        set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${Catch2_SOURCE_DIR}/contrib)

    endif()

endif()

find_library(LIB_NCURSES ncurses curses)

if(NOT LIB_NCURSES)
    message(STATUS "unable to find ncurses library, using fallback (no colors)")
    add_compile_definitions(RAYCHEL_USE_NCURSES_FALLBACK)

    set(LIB_NCURSES "")
endif()