#include "Board.h"
#include "Square.h"
#include <iostream>
#include <set>
#include <algorithm>

Board::Board(std::vector<std::vector<int>>& numbers) {
    numbers_on_the_board = numbers;
}

Board::Board() {
    std::vector<int> square1 = {5, 3, 0, 0, 7, 0, 0, 0, 2};
    std::vector<int> square2 = {6, 7, 2, 1, 0, 5, 0, 4, 0};
    std::vector<int> square3 = {1, 0, 0, 0, 0, 2, 5, 0, 7};
    std::vector<int> square4 = {0, 0, 0, 7, 6, 0, 4, 0, 3};
    std::vector<int> square5 = {4, 0, 6, 8, 0, 3, 0, 9, 1};
    std::vector<int> square6 = {0, 1, 0, 9, 0, 4, 8, 0, 6};
    std::vector<int> square7 = {9, 6, 1, 0, 3, 7, 2, 8, 0};
    std::vector<int> square8 = {2, 8, 0, 0, 1, 9, 6, 0, 5};
    std::vector<int> square9 = {0, 4, 0, 2, 8, 6, 1, 0, 9};
    numbers_on_the_board = std::vector<std::vector<int>>{square1, square2, square3, square4,
                                                         square5, square6, square7, square8, square9};
}

int Board::get_box_index(int i, int j) {
    int horizontal_index = i % 3;
    int vertical_index = j % 3;
    int index = (horizontal_index + 10) * (vertical_index + 1);
    switch (index) {
        case 10:
            return 0;
            break;
        case 20:
            return 1;
            break;
        case 30:
            return 2;
            break;
        case 11:
            return 3;
            break;
        case 22:
            return 4;
            break;
        case 33:
            return 5;
            break;
        case 12:
            return 6;
            break;
        case 24:
            return 7;
            break;
        case 36:
            return 8;
            break;
    }
}

std::vector<std::vector<int>> Board::gen_horizontal_lines(){
    std::vector<std::vector<int>> result = {};
    for(int currLine = 0; currLine < 9; currLine++) {
        std::vector<int> currVec = {};
        int startVec = 0;
        if (currLine < 6 && currLine >= 3) startVec = 3;
        if (currLine < 9 && currLine >= 6) startVec = 6;
        for(int i = startVec; i < startVec + 3; i++) {
            int startRange = currLine % 3;
            for(int j=0; j<3; j++) {
                currVec.push_back(numbers_on_the_board[i][startRange * 3 + j]);
            }
        }
        result.push_back(currVec);
    }
    return result;
}

std::vector<std::vector<int>> Board::gen_vertical_lines() {
    std::vector<std::vector<int>> result = {};
    for(int currLine = 0; currLine < 9; currLine++) {
        std::vector<int> currVec = {};
        int startVec = 0;
        if (currLine < 6 && currLine >= 3) startVec = 1;
        if (currLine < 9 && currLine >= 6) startVec = 2;
        for(int i = startVec; i < startVec + 7; i+=3) {
            int startRange = currLine % 3;
            for(int j=0; j<3; j++) {
                currVec.push_back(numbers_on_the_board[i][startRange + (3 * j)]);
            }
        }
        result.push_back(currVec);
    }
    return result;
}


void Board::draw() {
    std::vector<std::vector<int>> lines = Board::gen_horizontal_lines();
    for(int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            std::cout << "| " << (lines[i][j] == 0 ? " " : std::to_string(lines[i][j])) << " ";
            if (j == 8) {
                std::cout << "|";
            }
        }
        std::cout << "\n";
    }
}

void Board::fill_square_vector(std::vector<Square>& squares) {
    for(int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (numbers_on_the_board[i][j] == 0) {
                squares.emplace_back(i, j);
            }
        }
    }
}

void Board::solve() {
    bool should_continue = true;
    std::vector<Square> squares = {};
    fill_square_vector(squares);
    while (should_continue) {
        int initCount = squares.size();
        std::vector<std::vector<int>> horizontal_lines = Board::gen_horizontal_lines();
        std::vector<std::vector<int>> vertical_lines = Board::gen_vertical_lines();
        std::vector<std::vector<int>> boxes = numbers_on_the_board;

        should_continue = initCount != squares.size();
    }
}

// 1) fill up the squares vector with all squares that have the value 0 - x is x, y is y, the vector is empty
// 2) Loop begins and ends when nothing changes
// 3) Figure out numbers it cannot be by looking at every line and the box for every square and put it all in the vector
// 4) Loop through every box, and line. Figure out if there is a number in there that can only be present in one of them
//                if (numbers_on_the_board[i][j] == 0) {
//                    std::vector<int> horizontal_line = horizontal_lines[i];
//                    std::vector<int> vertical_line = vertical_lines[j];
//                    std::vector<int> box = boxes[Board::get_box_index(i, j)];
//
//                    std::vector<int> nums_inside = horizontal_line;
//                    nums_inside.insert(nums_inside.end(), vertical_line.begin(), vertical_line.end());
//                    nums_inside.insert(nums_inside.end(), box.begin(), box.end());
//                    std::set<int> distinct_elements(nums_inside.begin(), nums_inside.end());
//                    std::vector<int> impossible_nums(distinct_elements.begin(), distinct_elements.end());
//                    if (impossible_nums.size() == 8) {
//                        for(int l = 1; l <= 9; l++) {
//                            auto val = std::find(impossible_nums.begin(), impossible_nums.end(), l);
//                            if (val == impossible_nums.end()) {
//                                numbers_on_the_board[i][j] = l;
//                                should_continue = true;
//                            }
//                        }
//                    }
//                }
//            }
//        }