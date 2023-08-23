//
// Created by mihas on 21/08/2023.
//

#include <vector>
#include "Square.h"

#ifndef SUDOKU_GENERATOR_BOARD_H
#define SUDOKU_GENERATOR_BOARD_H


class Board {
private:
    std::vector<std::vector<int>> numbers_on_the_board;
    std::vector<std::vector<int>> gen_horizontal_lines();
    std::vector<std::vector<int>> gen_vertical_lines();
    int get_box_index(int i, int j);

public:
    explicit Board(std::vector<std::vector<int>>& numbers);
    Board();

    void fill_square_vector(std::vector<Square>& squares);

    void draw();
    void solve();
};


#endif //SUDOKU_GENERATOR_BOARD_H

// format: 9 arrays, each array represents its respective box and has 9 numbers

