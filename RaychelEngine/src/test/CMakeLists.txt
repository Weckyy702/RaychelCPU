cmake_minimum_required(VERSION 3.14)

project(Raychel_test)

if(NOT CATCH_2_EXTERNAL)
    find_package(Catch2 CONFIG REQUIRED)
endif()

file(GLOB_RECURSE RAYCHEL_TEST_SOURCES "*.test.cpp")

add_executable(Unit_test
    ${RAYCHEL_TEST_SOURCES}
)



target_include_directories(Unit_test PUBLIC
    ${RAYCHEL_INCLUDE_DIR}
)

target_compile_options(Unit_test PUBLIC
    ${RAYCHEL_COMPILE_FLAGS}
)

if(MSVC)
    target_compile_options(Unit_test PUBLIC
        /WX
    )
else()
    target_compile_options(Unit_test PUBLIC
        -Werror
    )
endif()

target_compile_features(Unit_test PUBLIC cxx_std_17)



target_link_libraries(Unit_test PUBLIC
    RaychelLogger
    Catch2::Catch2
)

if(LINK_GSL)
    target_link_libraries(Unit_test PUBLIC
        GSL
    )
endif()

include(Catch)
catch_discover_tests(Unit_test)



add_executable(RaychelCPU_test
    main.cpp
)

target_compile_options(RaychelCPU_test PUBLIC
    ${RAYCHEL_COMPILE_FLAGS}
)

target_link_libraries(RaychelCPU_test PRIVATE
    RaychelLogger
    Raychel
)