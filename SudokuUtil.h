//
// Created by mihas on 29/08/2023.
//
#include <vector>
#include <algorithm>

#ifndef SUDOKU_GENERATOR_SUDOKUUTIL_H
#define SUDOKU_GENERATOR_SUDOKUUTIL_H


class SudokuUtil {
public:
    static void eliminate_impossible_nums(const std::vector<int>& horizontal_lines, const std::vector<int>& vertical_lines,
                                          const std::vector<int>& boxes, std::vector<int>& possible_nums);
    static int get_box_index(int i, int j);

};


#endif //SUDOKU_GENERATOR_SUDOKUUTIL_H
