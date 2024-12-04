cmake_minimum_required(VERSION 3.29)
project(x86_emulator C)

set(CMAKE_C_STANDARD 23)

add_executable(x86_emulator emulator.c
        cpu.c
        cpu.h
        memory.c
        memory.h)
