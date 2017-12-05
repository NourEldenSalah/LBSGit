cmake_minimum_required(VERSION 3.8)
project(LibrarySystem)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c Book.h MeM.h Admin.h Admin.c Book.c MeM.c main.h)
add_executable(LibrarySystem ${SOURCE_FILES})