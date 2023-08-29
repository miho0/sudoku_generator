//
// Created by mihas on 29/08/2023.
//

#include "SudokuUtil.h"

void SudokuUtil::eliminate_impossible_nums(const std::vector<int> &horizontal_line, const std::vector<int> &vertical_line,
                                      const std::vector<int> &box, std::vector<int> &possible_nums) {
    std::vector<int> all_nums = {};

    for (int i = 0; i < 9; i++) {
        all_nums.push_back(horizontal_line[i]);
        all_nums.push_back(vertical_line[i]);
        all_nums.push_back(box[i]);
    }

    for (int i = 0; i < 27; i++) {
        auto it = std::find(possible_nums.begin(), possible_nums.end(), all_nums[i]);
        if (it != possible_nums.end()) {
            possible_nums.erase(it);
        }
    }
}

int SudokuUtil::get_box_index(int x, int y) {
    int horizontal_index = x / 3;
    int vertical_index = y / 3;
    int index = (horizontal_index + 10) * (vertical_index + 1);
    switch (index) {
        case 10:
            return 0;
        case 20:
            return 1;
        case 30:
            return 2;
        case 11:
            return 3;
        case 22:
            return 4;
        case 33:
            return 5;
        case 12:
            return 6;
        case 24:
            return 7;
        case 36:
            return 8;
        default:
            return -1;
    }
}