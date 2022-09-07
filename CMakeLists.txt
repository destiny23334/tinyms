cmake_minimum_required(VERSION 3.20)
project(TinyMS VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(./Include)

aux_source_directory(./Source SOURCE_FILE)
aux_source_directory(./ SOURCE_FILE)


add_executable(TinyMS ${SOURCE_FILE})