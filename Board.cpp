#include "Board.h"
#include <iostream>
#include <algorithm>

Board::Board(std::vector<std::vector<int>>& numbers) {
    numbers_on_the_board = numbers;
}

Board::Board() {
    std::vector<int> square1 = {4, 3, 5, 6, 8, 2, 1, 9, 7};
    std::vector<int> square2 = {2, 6, 9, 5, 7, 1, 8, 3, 4};
    std::vector<int> square3 = {7, 8, 1, 4, 9, 3, 5, 6, 2};
    std::vector<int> square4 = {8, 2, 6, 3, 7, 4, 9, 5, 1};
    std::vector<int> square5 = {1, 9, 5, 6, 8, 2, 7, 4, 3};
    std::vector<int> square6 = {3, 4, 7, 9, 1, 0, 6, 2, 8};
    std::vector<int> square7 = {5, 1, 9, 2, 4, 8, 7, 6, 3};
    std::vector<int> square8 = {3, 2, 6, 9, 5, 7, 4, 1, 8};
    std::vector<int> square9 = {8, 7, 4, 1, 3, 6, 2, 5, 9};
    numbers_on_the_board = std::vector<std::vector<int>>{square1, square2, square3, square4,
                                                         square5, square6, square7, square8, square9};
}

int Board::get_box_index(int x, int y) {
    int horizontal_index = x % 3;
    int vertical_index = y % 3;
    int index = (horizontal_index + 10) * (vertical_index + 1);
    switch (index) {
        case 10: return 0;
        case 20: return 1;
        case 30: return 2;
        case 11: return 3;
        case 22: return 4;
        case 33: return 5;
        case 12: return 6;
        case 24: return 7;
        case 36: return 8;
        default: return -1;
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
    std::vector<std::vector<int>> horizontal_lines = gen_horizontal_lines();
    for(int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (horizontal_lines[i][j] == 0) {
                squares.emplace_back(i, j);
            }
        }
    }
}

void Board::eliminate_impossible_nums(const std::vector<int>& horizontal_line, const std::vector<int>& vertical_line,
                                                  const std::vector<int>& box, std::vector<int>& possible_nums) {
    std::vector<int> all_nums = {};

    for (int i = 0; i < 9; i++) {
        all_nums.push_back(horizontal_line[i]);
        all_nums.push_back(vertical_line[i]);
        all_nums.push_back(box[i]);
    }

    for(int i = 0; i < 27; i++) {
        auto it = std::find(possible_nums.begin(), possible_nums.end(), all_nums[i]);
        if (it != possible_nums.end()) {
            possible_nums.erase(it);
        }
    }
}

void Board::simplify(std::vector<Square> squares) {
    for(Square & s : squares) {
        if (s.possible_nums.size() == 1) {
            this->numbers_on_the_board[s.x][s.y] = s.possible_nums[0];
        }
    }
}

void Board::solve() {
    bool should_continue = true;
    std::vector<Square> squares = {};
    fill_square_vector(squares);
    while (should_continue) {
        int init_count = squares.size();
        std::vector<std::vector<int>> horizontal_lines = Board::gen_horizontal_lines();
        std::vector<std::vector<int>> vertical_lines = Board::gen_vertical_lines();
        std::vector<std::vector<int>> boxes = numbers_on_the_board;

        for(int i = 0; i < init_count; i++) {
            std::vector<int> horizontal_line = horizontal_lines[squares[i].x];
            std::vector<int> vertical_line = vertical_lines[squares[i].y];
            std::vector<int> box = boxes[get_box_index(squares[i].x, squares[i].y)];
            eliminate_impossible_nums(horizontal_line, vertical_line, box, squares[i].possible_nums);
        }

        simplify(squares);

        should_continue = init_count != squares.size();
    }
}

// 1) fill up the squares vector with all squares that have the value 0 - x is x, y is y, the vector is empty
// 2) Loop begins and ends when nothing changes
// 3) Figure out numbers it cannot be by looking at every line and the box for every square and put it all in the vector
// 4) Loop through every box, and line. Figure out if there is a number in there that can only be present in one of them
// 5) Update the main vector