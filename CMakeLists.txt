cmake_minimum_required(VERSION 3.20)

project(
    DataStructure
    LANGUAGES C
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTest)
include(FetchContent)

set(SDL_SHARED OFF CACHE BOOL "Build SDL shared library")
set(SDL_STATIC ON CACHE BOOL "Build SDL static library")

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.4.16
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(SDL3)

add_subdirectory(LinearList/SequenceList)
add_subdirectory(LinearList/LinkedList)