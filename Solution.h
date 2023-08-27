//
// Created by mihas on 27/08/2023.
//

class Solution {
private:
    int horizontal;
    int vertical;
    int box;
    int num;
public:
    Solution(int h, int v, int b, int n) {
        horizontal = h;
        vertical = v;
        box = b;
        num = n;
    }

    // checks if the squares are related in any way, not if they are the same
    bool operator==(const Solution& other) const {
        return (horizontal == other.horizontal || vertical == other.vertical || box == other.box);
    }

    int get_num() const {
        return num;
    }
    void set_num(int n) {
        num = n;
    }

};

#ifndef SUDOKU_GENERATOR_SOLUTION_H
#define SUDOKU_GENERATOR_SOLUTION_H

#endif //SUDOKU_GENERATOR_SOLUTION_H
