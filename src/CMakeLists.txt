cmake_minimum_required(VERSION 3.19)
project(Coursework2 C)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_STANDARD 11)

include_directories(..)

add_executable(Coursework2 Coursework2.c Renderer.c FileIO.c Terminal.c TextHandler.c Library.c Commands.c ChangeLog.c)