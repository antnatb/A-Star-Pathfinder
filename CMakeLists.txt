cmake_minimum_required(VERSION 3.20)
project(Pathfinder)

set(CMAKE_CXX_STANDARD 14)

if (WIN32)
    set(BUILD_SHARED_LIBS OFF)
endif()

# set SFML library
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio REQUIRED)
include_directories(SFML/include)

add_library(core Cell.cpp Cell.h Grid.cpp Grid.h)

target_link_libraries(core PUBLIC sfml-system sfml-window sfml-graphics sfml-audio)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(Pathfinder main.cpp Grid.cpp Grid.h Cell.cpp Cell.h)
target_link_libraries(Pathfinder PUBLIC core)
