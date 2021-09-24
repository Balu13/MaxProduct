#pragma once

#include <utility>

class NumberProducts {
public:
    enum class Direction
    {
        Horizontal, Vertical, Diagonal
    };

    NumberProducts(int number, int adjacentNum) : _number(number),
        adjacentNumber(adjacentNum),
        horizontal(number),
        vertical(number),
        diagonal(number)
    {}

    int getNumber() const
    {
        return _number;
    }

    // these functions return current product in the direction and number of factors in that direction
    std::pair<int, int> addHorizontalFactor(int factor);
    std::pair<int, int> addVerticalFactor(int factor);
    std::pair<int, int> addDiagonalFactor(int factor);

private:
    int _number;
    int adjacentNumber;
    int horizontal;
    int vertical;
    int diagonal;

    int horizontalFactorsNum{ 1 };
    int verticalFactorsNum{ 1 };
    int diagonalFactorsNum{ 1 };
};
