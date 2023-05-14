# Multithread program

This repository contains the multithread project for MC504 - Operating Systems

## Overview

The objective of this project is to adapt and enchance the barbershop problem. Working with threads, mutexes, semaphores , multithreading in general etc.

## Using CMake

CMake is a tool that automates the build processes. Check the `CMakeLists.txt` file to see how it finds and links your program against the `pthreads` lib.

## How to Run the Code

After cloning the repository, run:

```sh
 mkdir build
 cd build
 cmake ..
 make
```

This will create the executables in the build folder. To compile again, simply run `make`.
