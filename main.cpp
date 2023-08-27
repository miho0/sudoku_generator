#include <iostream>
#include "Board.h"

// input: [1, 5, 6, 9, ...], [5, 8, 10, 70, ...]


int main() {
    Board board = Board();
    board.draw();
    board.solve();
    std::cout<<"--------------\n";
    board.draw();

    Solution s1 = Solution(7, 4, 7, 0);
    Solution s2 = Solution(6, 4, 7, 0);
    std::cout<<(s1 == s2)<<"\n";

    return 0;
}
