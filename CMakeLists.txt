cmake_minimum_required(VERSION 3.20)

# Project name
project(csv2parquet LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find required packages
find_package(Arrow REQUIRED)
find_package(Parquet REQUIRED)

# Create executable
add_executable(csv2parquet main.cpp)

# Link libraries
target_link_libraries(csv2parquet PRIVATE arrow_shared parquet_shared)

