cmake_minimum_required(VERSION 3.20)

project(
    DataStructure
    LANGUAGES C
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTEST)

add_subdirectory(LinearList/SequenceList)