#include <iostream>
#include "Board.h"

// input: [1, 5, 6, 9, ...], [5, 8, 10, 70, ...]


int main() {
    Board board = Board();
    board.solve();
    board.draw();
    return 0;
}
