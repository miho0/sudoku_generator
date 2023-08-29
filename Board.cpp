#include "Board.h"
#include <iostream>

Board::Board(std::vector<std::vector<int>> &numbers) {
    horizontal_lines = numbers;
    missing_numbers = std::vector<Square>{};
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

void Board::output() {
    for(int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            std::cout<<horizontal_lines[i][j];
        }
    }
}

void Board::fill_missing_nums() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (horizontal_lines[i][j] == 0) {
                missing_numbers.emplace_back(i, j);
            }
        }
    }
}

void Board::initial_solutions() {
    bool should_continue = true;
    while(should_continue) {
        should_continue = false;
        std::vector<std::vector<int>> vertical_lines = Board::gen_vertical_lines();
        std::vector<std::vector<int>> boxes = gen_boxes();

        for (auto &square: missing_numbers) {
            std::vector<int> horizontal_line = horizontal_lines[square.x];
            std::vector<int> vertical_line = vertical_lines[square.y];
            std::vector<int> box = boxes[SudokuUtil::get_box_index(square.x, square.y)];
            SudokuUtil::eliminate_impossible_nums(horizontal_line, vertical_line, box, square.possible_nums);
        }

        for (int i = 0; i < missing_numbers.size(); i++) {
            Square &s = missing_numbers[i];
            if (s.possible_nums.size() == 1) {
                this->horizontal_lines[s.x][s.y] = s.possible_nums[0];
                missing_numbers.erase(missing_numbers.begin() + i);
                should_continue = true;
            }
        }
    }
}

void Board::fill_solutions_initial() {
    for(auto & missing_number : missing_numbers) {
        int x = missing_number.x;
        int y = missing_number.y;
        solutions.emplace_back(x, y, SudokuUtil::get_box_index(x, y), 0);
    }
}

// in the solution structure, we have the index of the horizontal, vertical lines and box
// check all previous values to see if any of them have the same line or box and if we put that number in there already

bool Board::backtrack(int index = 0) {
    if (index >= missing_numbers.size()) {
        return true;
    }
    for(int number: missing_numbers[index].possible_nums) {
        bool solution_works = true;
        for(int i = 0; i <= index; i++) {
            if (solutions[index] == solutions[i] && number == solutions[i].get_num()) {
                solution_works = false;
                break;
            }
        }
        if (solution_works) {
            solutions[index].set_num(number);
            if (backtrack(index + 1)) {
                return true;
            } else {
                solutions[index].set_num(0);
            }
        }
    }
    return false;
}

void Board::fill_solutions() {
    for(int i = 0; i < solutions.size(); i++) {
        int x = missing_numbers[i].x;
        int y = missing_numbers[i].y;
        horizontal_lines[x][y] = solutions[i].get_num();
    }
}

void Board::solve() {
    fill_missing_nums(); // we fill our missing nums vector with appropriate values
    initial_solutions(); // we generate the initial solutions and eliminate numbers that it cannot be
    fill_solutions_initial(); // we fill the solutions vector with the initial values
    bool solved = backtrack();
    // std::cout<<(solved ? "Sudoku solved!" : "Unable to find a solution");
    fill_solutions();
}

// 1) solve for the solvable missing_numbers and remove numbers that it cannot be from the missing_numbers structure
// 2) backtracking algorithm - try a number out of possible_nums - have another vector that stores all values that we have decided to be inside
// 3) remove that number from possible_nums from all missing_numbers that are related to that square, remember what we have removed in order for this to work
// 4) how do we know the solution doesn't work? If there are no possible_nums in there
