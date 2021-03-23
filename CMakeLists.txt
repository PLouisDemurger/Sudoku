cmake_minimum_required(VERSION 3.17)
project(Sudoku C)

set(CMAKE_C_STANDARD 99)
set(SOURCE_FILE lib)
set(HEADER_FILE include)


add_executable(Sudoku main.c ${SOURCE_FILE}/sudokuFunction.c ${HEADER_FILE}/sudokuFunction.h)