cmake_minimum_required(VERSION 3.14)

project(Raychel_test)

find_package(Catch2 REQUIRED)


file(GLOB_RECURSE RAYCHEL_TEST_SOURCES "*.test.cpp")

add_executable(Unit_test
    ${RAYCHEL_TEST_SOURCES}
)


target_include_directories(Unit_test PUBLIC
    ${RAYCHEL_INCLUDE_DIR}
)
target_compile_features(Unit_test PUBLIC cxx_std_17)


target_link_libraries(Unit_test PUBLIC
    RaychelLogger
    Catch2::Catch2
)


include(Catch)
catch_discover_tests(Unit_test)