# CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(Asteroids)

# Define C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Define source directories: "include" is for headers and "src" is for implementation
include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
)

# Define a list, called SRC_FILES, that stores all source code files within "include" and "src"
file(GLOB_RECURSE SRC_FILES
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

# Move font files to build-unix/
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/include/fonts
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
# Move texture files to build-unix/
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/include/textures
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
# Include all source code files to generate an executable
add_executable(Asteroids ${SRC_FILES})

# Link SFML libraries to the executable
target_link_libraries(Asteroids sfml-graphics sfml-window sfml-system)
