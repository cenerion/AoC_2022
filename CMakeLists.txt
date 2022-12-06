cmake_minimum_required(VERSION 3.24)
cmake_policy(SET CMP0054 NEW)

project("AoC2022")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "-W4 -WX -EHsc")
else()
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wshadow -Wconversion -Wpedantic -Werror")
endif()


add_executable(Day1 ./Day1/day1.cpp)
add_executable(Day2 ./Day2/day2.cpp)
add_executable(Day3 ./Day3/day3.cpp)
add_executable(Day4 ./Day4/day4.cpp)
