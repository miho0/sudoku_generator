#include <iostream>
#include "Board.h"

bool solve_for_input(int argc, char *argv[]) {
    if (argc != 83) {
        return false;
    }
    int k = 2;
    std::vector<std::vector<int>> horizontal_lines = std::vector<std::vector<int>>();
    for(int i = 0; i < 9; i++) {
        std::vector<int> curr_line = {};
        curr_line.reserve(9);
        for (int j = 0; j < 9; j++) {
            curr_line.push_back(*argv[k] - '0');
            k++;
        }
        horizontal_lines.push_back(curr_line);
    }

    Board board = Board(horizontal_lines);
    board.solve();
    board.output();
}

int main(int argc, char *argv[]) {
    std::vector<int> nums = std::vector<int>();
    switch(*argv[1]) {
        case 's':
            solve_for_input(argc, argv);
            break;
        case 'g':
            std::cout<<"Not yet implemented";
            break;
        default:
            std::cout<<"Wrong operation code";
            break;
    }
    return 0;
}
