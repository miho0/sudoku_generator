#include <vector>
#include "Square.h"
#include <algorithm>

//
// Created by miha.mok on 24. 08. 2023.
//

#ifndef SUDOKU_GENERATOR_SUDOKUENTITY_H
#define SUDOKU_GENERATOR_SUDOKUENTITY_H

// a struct that has x, y and the value that it has to be
struct SolutionForSquare {
    int x;
    int y;
    int num;

    SolutionForSquare(int x1, int y1, int num1) {
        x = x1;
        y = y1;
        num = num1;
    }
};

// entity has a list of squares that are associated with it and a list of missing numbers
// TODO write a function that takes one of these as a parameter and removes the numbers that it cannot be, then use the simplify function of the Board class

class SudokuEntity {
public:
    std::vector<Square> squares;
    std::vector<int> missing_numbers;

    SudokuEntity();
    std::vector<SolutionForSquare> solve_for_solvable_squares();
};


#endif //SUDOKU_GENERATOR_SUDOKUENTITY_H
