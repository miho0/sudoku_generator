#include <vector>

struct Square{
    int x;
    int y;
    std::vector<int> impossibleNums;

public:
    Square(int x, int y) {
        this->x = x;
        this->y = y;
        impossibleNums = {};
    }
};