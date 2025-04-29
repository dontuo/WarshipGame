cmake_minimum_required(VERSION 3.10) 
project(WarshipGame)

set(CMAKE_CXX_STANDARD 20)

#raylib
#uncomment this for wayland support
#set(GLFW_BUILD_WAYLAND ON)
add_subdirectory(libs/raylib)
include_directories(libs/raylib/src)

#clay. For UI
include_directories(libs/clay)

#Find all source files in the src directory
file(GLOB SOURCES "src/*.hpp"
                  "src/*.cpp")

#Define the executable
add_executable(WarshipGame ${SOURCES})

#Link the libraries
target_link_libraries(${PROJECT_NAME} raylib)
