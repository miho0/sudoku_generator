#include <vector>

struct Square{
public:
    int x;
    int y;
    std::vector<int> possible_nums;
    Square(int x, int y) {
        this->x = x;
        this->y = y;
        possible_nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    }

    bool operator==(const Square& other) const {
        return (x == other.x) && (y == other.y);
    }
};