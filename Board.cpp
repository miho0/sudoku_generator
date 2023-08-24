#include "Board.h"
#include <iostream>
#include <algorithm>

Board::Board(std::vector<std::vector<int>> &numbers) {
    horizontal_lines = numbers;
}

Board::Board() {
    std::vector<int> l1 = {1, 0, 0, 4, 0, 6, 7, 8, 9};
    std::vector<int> l2 = {0, 0, 6, 0, 8, 0, 1, 0, 0};
    std::vector<int> l3 = {7, 0, 0, 0, 2, 3, 0, 0, 0};
    std::vector<int> l4 = {0, 0, 0, 5, 0, 0, 8, 0, 1};
    std::vector<int> l5 = {0, 0, 0, 0, 9, 1, 2, 3, 0};
    std::vector<int> l6 = {0, 0, 1, 0, 3, 0, 0, 0, 7};
    std::vector<int> l7 = {3, 4, 0, 6, 0, 0, 0, 0, 0};
    std::vector<int> l8 = {0, 7, 8, 0, 0, 2, 0, 0, 0};
    std::vector<int> l9 = {0, 1, 2, 3, 0, 5, 6, 0, 8};
    horizontal_lines = std::vector<std::vector<int>>{l1, l2, l3, l4, l5, l6, l7, l8, l9};
    squares = std::vector<Square>{};
}

int Board::get_box_index(int x, int y) {
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

std::vector<std::vector<int>> Board::gen_boxes() {
    std::vector<std::vector<int>> result = {};
    for (int currLine = 0; currLine < 9; currLine++) {
        std::vector<int> currVec = {};
        int startVec = 0;
        if (currLine < 6 && currLine >= 3) startVec = 3;
        if (currLine >= 6) startVec = 6;
        for (int i = startVec; i < startVec + 3; i++) {
            int startRange = currLine % 3;
            for (int j = 0; j < 3; j++) {
                currVec.push_back(horizontal_lines[i][startRange * 3 + j]);
            }
        }
        result.push_back(currVec);
    }
    return result;
}

std::vector<std::vector<int>> Board::gen_vertical_lines() {
    std::vector<std::vector<int>> result = {};
    for (int currLine = 0; currLine < 9; currLine++) {
        std::vector<int> currVec = {};
        currVec.reserve(9);
        for (int j = 0; j < 9; j++) {
            currVec.push_back(horizontal_lines[j][currLine]);
        }
        result.push_back(currVec);
    }
    return result;
}


void Board::draw() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            std::cout << "| " << (horizontal_lines[i][j] == 0 ? " " : std::to_string(horizontal_lines[i][j])) << " ";
            if (j == 8) {
                std::cout << "|";
            }
        }
        std::cout << "\n";
    }
}

void Board::fill_square_vector() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (horizontal_lines[i][j] == 0) {
                squares.emplace_back(i, j);
            }
        }
    }
}

void Board::eliminate_impossible_nums(const std::vector<int> &horizontal_line, const std::vector<int> &vertical_line,
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

void Board::find_square(int x, int y, std::vector<Square> &entity_squares) {
    for (auto &square: squares) {
        if (square.x == x && square.y == y) {
            entity_squares.push_back(square);
        }
    }
}

void Board::fill_solvable_squares(const std::vector<SolutionForSquare> &solutions) {
    for (auto &square: squares) {
        for (auto solution: solutions) {
            if (square.x == solution.x && square.y == solution.y) {
                horizontal_lines[square.x][square.y] = solution.num;
                auto it = std::find(squares.begin(), squares.end(), square);
                squares.erase(it);
            }
        }
    }
}

bool Board::only_possible_number_approach() {
    bool should_continue = false;
    std::vector<std::vector<int>> vertical_lines = Board::gen_vertical_lines();
    std::vector<std::vector<int>> boxes = gen_boxes();

    for (auto &square: squares) {
        std::vector<int> horizontal_line = horizontal_lines[square.x];
        std::vector<int> vertical_line = vertical_lines[square.y];
        std::vector<int> box = boxes[get_box_index(square.x, square.y)];
        eliminate_impossible_nums(horizontal_line, vertical_line, box, square.possible_nums);
    }

    for (int i = 0; i < squares.size(); i++) {
        Square &s = squares[i];
        if (s.possible_nums.size() == 1) {
            this->horizontal_lines[s.x][s.y] = s.possible_nums[0];
            squares.erase(squares.begin() + i);
            should_continue = true;
        }
    }
    return should_continue;
}

bool Board::missing_number_approach() {
    // for each box, horizontal and vertical line, construct a SudokuEntity instance
    // use the solve function to get the solutions
    // update the numbers
    bool should_continue = false;
    for (int i = 0; i < horizontal_lines.size(); i++) {
        SudokuEntity entity = SudokuEntity();
        for (int j = 0; j < 9; j++) {
            if (horizontal_lines[i][j] == 0) {
                find_square(i, j, entity.squares);
            } else {
                auto it = std::find(entity.missing_numbers.begin(), entity.missing_numbers.end(),
                                    horizontal_lines[i][j]);
                if (it != entity.missing_numbers.end()) {
                    entity.missing_numbers.erase(it);
                }
            }
        }
        std::vector<SolutionForSquare> solutions_generated = entity.solve_for_solvable_squares();
        if (!solutions_generated.empty()) {
            should_continue = true;
            fill_solvable_squares(solutions_generated);
        }
    }
return should_continue;
}

void Board::solve() {
    // TODO maybe move the loop and the calls to the simplify function here. Figure out the optimal approach
    // current idea:
    // 1) do the only possible number approach until it doesn't do anything anymore
    // 2) do the missing numbers approach one
    // repeat the process; once it doesn't do anything anymore, can we declare the sudoku as having multiple solutions?
    bool should_continue = true;
    fill_square_vector();
    while (should_continue) {
        bool should_continue_first_approach = true;
        while (should_continue_first_approach) {
            should_continue_first_approach = only_possible_number_approach();
        }
        should_continue = missing_number_approach();
    }
}

// 1) fill up the squares vector with all squares that have the value 0 - x is x, y is y, the vector is empty
// 2) Loop begins and ends when nothing changes
// 3) Figure out numbers it cannot be by looking at every line and the box for every square and put it all in the vector
// 4) Loop through every box, and line. Figure out if there is a number in there that can only be present in one of them
// 5) Update the main vector

// a struct that keeps track of everything

// horizontal lines:

// loop through every line
// get the missing numbers
//

// TODO idea: keep track of the lines that are already solved; don't solve them again :)
// TODO idea: keep track of the SudokuEntities so you can pick upp where you left off