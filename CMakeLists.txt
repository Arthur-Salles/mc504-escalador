cmake_minimum_required(VERSION 3.5)

project(oito_encaixes)

# Set compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pthread")

# Create executable
add_executable(oito_encaixes src/oito_encaixes.c)

# Link pthreads library
target_link_libraries(oito_encaixes pthread)
