cmake_minimum_required(VERSION 3.21)
project(sudoku_generator)

set(CMAKE_CXX_STANDARD 14)

add_executable(sudoku_generator
        main.cpp
        Board.cpp Board.h
        Square.h
        SudokuUtil.cpp
        SudokuUtil.h
        )
