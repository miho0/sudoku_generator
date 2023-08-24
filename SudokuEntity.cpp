//
// Created by miha.mok on 24. 08. 2023.
//

#include "SudokuEntity.h"

SudokuEntity::SudokuEntity() {
    missing_numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    squares = {};
}

std::vector<SolutionForSquare> SudokuEntity::solve_for_solvable_squares() {
    std::vector<SolutionForSquare> solutions;
    for(int missing_number : missing_numbers) {
        bool should_continue = true;
        bool should_update = true;
        int x;
        int y;
        for(auto & square : squares) {
            std::vector<int> possible_nums = square.possible_nums;
            auto it = std::find(possible_nums.begin(), possible_nums.end(), missing_number);
            if (it != possible_nums.end()) {
                if (should_continue) {
                    should_continue = false;
                    x = square.x;
                    y = square.y;
                }
            } else {
                should_update = false;
                break;
            }
        }
        if (should_update) {
            solutions.emplace_back(x, y, missing_number);
        }
    }

    return solutions;
}

// loop through all missing numbers
// loop through all squares
// if a number is possible, check if should_continue is true
// if it is true, set it to false, set x and y and continue
// if it is false, stop and continue with the next number
// if we go through every one, create the solutionForSquare and put it in the return vector