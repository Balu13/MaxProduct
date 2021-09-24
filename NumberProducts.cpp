#include "NumberProducts.h"

std::pair<int, int> NumberProducts::addHorizontalFactor(int factor)
{
    int factorsNum{ -1 };

    if (horizontalFactorsNum < adjacentNumber)
    {
        horizontal *= factor;
        factorsNum = ++horizontalFactorsNum;
    }

    return { horizontal, factorsNum };
}

std::pair<int, int> NumberProducts::addVerticalFactor(int factor)
{
    int factorsNum{ -1 };

    if (verticalFactorsNum < adjacentNumber)
    {
        vertical *= factor;
        factorsNum = ++verticalFactorsNum;
    }

    return { vertical, factorsNum };
}

std::pair<int, int> NumberProducts::addRightDiagonalFactor(int factor)
{
    int factorsNum{ -1 };

    if (rightDiagonalFactorsNum < adjacentNumber)
    {
        rightDiagonal *= factor;
        factorsNum = ++rightDiagonalFactorsNum;
    }

    return { rightDiagonal, factorsNum };
}

std::pair<int, int> NumberProducts::addLeftDiagonalFactor(int factor)
{
    int factorsNum{ -1 };

    if (leftDiagonalFactorsNum < adjacentNumber)
    {
        leftDiagonal *= factor;
        factorsNum = ++leftDiagonalFactorsNum;
    }

    return { leftDiagonal, factorsNum };
}
