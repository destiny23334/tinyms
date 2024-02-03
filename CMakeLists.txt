cmake_minimum_required(VERSION 3.20)
project(TinyMS VERSION 0.1.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(./tinyms/Include)

# tinyms
add_subdirectory(tinyms)

# test
add_subdirectory(Test)

# example
add_subdirectory(Example)


