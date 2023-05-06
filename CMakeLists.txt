cmake_minimum_required(VERSION 3.5)

project(chest_day)

# Set compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pthread")

# Create executable
add_executable(chest_day src/chest_day.c)

# Link pthreads library
target_link_libraries(chest_day pthread)
