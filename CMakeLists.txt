cmake_minimum_required(VERSION 3.10)

# Set your project name
project(RayTracer)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include the header files
include_directories(include)

# Add the executable from main.cpp
add_executable(RayTracer main.cpp)

