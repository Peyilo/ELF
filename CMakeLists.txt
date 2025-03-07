cmake_minimum_required(VERSION 3.27)
project(ELF C)

set(CMAKE_C_STANDARD 11)

add_executable(ELF main.c
        elf/elf.h
        elf/elf32.c
        elf/elf32.h
        elf/elf64.c
        elf/elf64.h
        elf/internal.h
        elf/elf.c)
