cmake_minimum_required(VERSION 3.28.3)

project(tests_lefosh C CXX)

set(Sources 
    tests.cpp
)

add_executable(${PROJECT_NAME} ${Sources})

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    gtest_main
    lefosh_static
)

add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
)
