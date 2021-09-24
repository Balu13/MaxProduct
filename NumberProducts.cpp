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

std::pair<int, int> NumberProducts::addDiagonalFactor(int factor)
{
    int factorsNum{ -1 };

    if (diagonalFactorsNum < adjacentNumber)
    {
        diagonal *= factor;
        factorsNum = ++diagonalFactorsNum;
    }

    return { diagonal, factorsNum };
}
