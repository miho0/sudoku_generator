//
// Created by mihas on 21/08/2023.
//

#include <vector>
#include "Square.h"
#include "Solution.h"

#ifndef SUDOKU_GENERATOR_BOARD_H
#define SUDOKU_GENERATOR_BOARD_H


class Board {
private:
    std::vector<std::vector<int>> horizontal_lines;
    std::vector<Square> missing_numbers;
    std::vector<Solution> solutions;
    std::vector<std::vector<int>> gen_boxes();
    std::vector<std::vector<int>> gen_vertical_lines();
    static void eliminate_impossible_nums(const std::vector<int>& horizontal_lines, const std::vector<int>& vertical_lines,
                                          const std::vector<int>& boxes, std::vector<int>& possible_nums);
    static int get_box_index(int i, int j);
    void initial_solutions();
    void fill_missing_nums();
    void fill_solutions_initial();
    bool backtrack(int index);
    void fill_solutions();

public:
    explicit Board(std::vector<std::vector<int>>& numbers);
    Board();

    void draw();
    void solve();
};


#endif //SUDOKU_GENERATOR_BOARD_H

// format: 9 arrays, each array represents its respective box and has 9 numbers

