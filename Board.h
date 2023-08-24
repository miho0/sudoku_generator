//
// Created by mihas on 21/08/2023.
//

#include <vector>
#include "SudokuEntity.h"

#ifndef SUDOKU_GENERATOR_BOARD_H
#define SUDOKU_GENERATOR_BOARD_H


class Board {
private:
    std::vector<std::vector<int>> horizontal_lines;
    std::vector<Square> squares;
    std::vector<std::vector<int>> gen_boxes();
    std::vector<std::vector<int>> gen_vertical_lines();
    static int get_box_index(int i, int j);
    void find_square(int x, int y, std::vector<Square>& entity_squares);
    bool only_possible_number_approach();
    bool missing_number_approach();
    void fill_solvable_squares(const std::vector<SolutionForSquare>& solutions);

public:
    explicit Board(std::vector<std::vector<int>>& numbers);
    Board();

    void fill_square_vector();
    static void eliminate_impossible_nums(const std::vector<int>& horizontal_lines, const std::vector<int>& vertical_lines,
                                                      const std::vector<int>& boxes, std::vector<int>& possible_nums);

    void draw();
    void solve();
};


#endif //SUDOKU_GENERATOR_BOARD_H

// format: 9 arrays, each array represents its respective box and has 9 numbers

