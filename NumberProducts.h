#pragma once

#include <utility>

class NumberProducts {
public:
    enum class Direction
    {
        Horizontal, Vertical, RightDiagonal, LeftDiagonal
    };

    NumberProducts(int number, int adjacentNum) : _number(number),
                                                  adjacentNumber(adjacentNum),
                                                  horizontal(number),
                                                  vertical(number),
                                                  rightDiagonal(number),
                                                  leftDiagonal(number)
    {}

    int getNumber() const
    {
        return _number;
    }

    // these functions return current product in the direction and number of factors in that direction
    std::pair<int, int> addHorizontalFactor(int factor);
    std::pair<int, int> addVerticalFactor(int factor);
    std::pair<int, int> addRightDiagonalFactor(int factor);
    std::pair<int, int> addLeftDiagonalFactor(int factor);

private:
    int _number;
    int adjacentNumber;
    int horizontal;
    int vertical;
    int rightDiagonal;
    int leftDiagonal;

    int horizontalFactorsNum{ 1 };
    int verticalFactorsNum{ 1 };
    int rightDiagonalFactorsNum{ 1 };
    int leftDiagonalFactorsNum{ 1 };
};
