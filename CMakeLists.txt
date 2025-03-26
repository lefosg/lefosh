cmake_minimum_required(VERSION 3.28.3)

project(lefosh C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(external/googletest)

set(Headers
    src/app/lefosh.hpp
)

set(Sources 
    src/app/lefosh.cpp
)

add_executable(${PROJECT_NAME} ${Sources} src/app/main.cpp)
add_library(${PROJECT_NAME}_static STATIC ${Sources})

add_subdirectory(tests)