cmake_minimum_required(VERSION 3.30)
project(x86_Emulator)

set(CMAKE_CXX_STANDARD 26)

add_executable(x86_Emulator main.cpp
        file_parser.cpp
        file_parser.h
        cpu.cpp
        cpu.h)
