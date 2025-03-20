cmake_minimum_required(VERSION 3.28.3)
project(lefosh LANGUAGES C)
add_executable(${PROJECT_NAME} src/app/lefosh.c)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# add_subdirectory(src/tests)

set(OSBits 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(OSBits 64)
endif()

set(FullOutputDir "${CMAKE-SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}${OSBits}/${CMAKE_BUILD_TYPE}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${FullOutputDir}/staticlibs")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${FullOutputDir}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${FullOutputDir}")