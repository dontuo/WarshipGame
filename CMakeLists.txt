cmake_minimum_required(VERSION 3.10)
project(WarshipGame)

set(CMAKE_CXX_STANDARD 17)

#raylib 
# uncomment this for wayland support 
#set(GLFW_BUILD_WAYLAND ON)
add_subdirectory(libs/raylib)
include_directories(libs/raylib/src)

# Find all source files in the src directory
file(GLOB SOURCES
     "src/*.hpp"
     "src/*.cpp"
)

# Define the executable
add_executable(WarshipGame ${SOURCES})

# Link the libraries
target_link_libraries(${PROJECT_NAME} raylib)

