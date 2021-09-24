#include "NumberProducts.h"

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <chrono>

static const char* txt = "08 02 22 97 38 15 00 40 00 75 04 05 07 78 52 12 50 77 91 08\n"
                        "d";
static const char* test =
    "55 62 22 07 16\n"
    "56 04 57 09 97\n"
    "04 54 20 75 11\n"
    "56 99 77 01 01\n"
    "33 66 11 44 22";

constexpr int adjacentNumber{ 4 };

std::vector<std::string> split(const std::string& inputString, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(inputString);
    std::string item;

    while (getline(ss, item, delimiter)) {
        result.push_back(item);
    }

    return result;
}

std::vector<std::vector<int>> parseNumberString(std::string numberString)
{
    std::vector<std::string> lines = split(numberString, '\n');
    std::vector<std::vector<int>> numbers;
    for (const std::string& line : lines)
    {
        std::vector<std::string> row = split(line, ' ');
        std::vector<int> numLine;
        for (std::string& strNumber : row)
        {
            numLine.push_back(atoi(strNumber.c_str()));
        }
        numbers.push_back(numLine);
    }

    return numbers;
}

// multiply previous numbers to the left (maximum <adjacentNumber> numbers)
void multiplyLeftNumbers(int colNo, int rowNo, int colNum, int factor,
                             std::vector<NumberProducts>& products,
                             std::tuple<int, int, NumberProducts::Direction>& max)
{
    for (int prevCol = colNo - 1; prevCol >= 0; --prevCol)
    {
        int prevPosition = rowNo * colNum + prevCol;
        auto multiplicationResult = products[prevPosition].addHorizontalFactor(factor);
        if (multiplicationResult.second == -1)
        {
            // all previous numbers to the left were multiplied
            break;
        }

        if (multiplicationResult.second == adjacentNumber
            && std::get<1>(max) < multiplicationResult.first)
        {
            // set new maximum
            max = { prevPosition, multiplicationResult.first, NumberProducts::Direction::Horizontal };
        }
    }
}

// multiply numbers above
void multiplyAboveNumbers(int colNo, int rowNo, int colNum, int factor,
    std::vector<NumberProducts>& products,
    std::tuple<int, int, NumberProducts::Direction>& max)
{
    for (int prevRow = rowNo - 1; prevRow >= 0; --prevRow)
    {
        int prevPosition = prevRow * colNum + colNo;
        auto multiplicationResult = products[prevPosition].addVerticalFactor(factor);
        if (multiplicationResult.second == -1)
        {
            // all previous numbers up were multiplied
            break;
        }

        if (multiplicationResult.second == adjacentNumber
            && std::get<1>(max) < multiplicationResult.first)
        {
            // set new maximum
            max = { prevPosition, multiplicationResult.first, NumberProducts::Direction::Vertical };
        }
    }
}

// multiply diagonal numbers
void multiplyDiagonalNumbers(int colNo, int rowNo, int colNum, int factor,
    std::vector<NumberProducts>& products,
    std::tuple<int, int, NumberProducts::Direction>& max)
{
    for (int prevRow = rowNo - 1, prevCol = colNo - 1; prevRow >= 0 && prevCol >= 0; --prevRow, -- prevCol)
    {
        int prevPosition = prevRow * colNum + prevCol;
        auto multiplicationResult = products[prevPosition].addDiagonalFactor(factor);
        if (multiplicationResult.second == -1)
        {
            // all previous numbers up were multiplied
            break;
        }

        if (multiplicationResult.second == adjacentNumber
            && std::get<1>(max) < multiplicationResult.first)
        {
            // set new maximum
            max = { prevPosition, multiplicationResult.first, NumberProducts::Direction::Diagonal };
        }
    }
}

int main()
{
    std::vector<std::vector<int>> numbers = parseNumberString(test);
    if (numbers.empty())
    {
        std::cout << "Illegal numbers string";
        return 0;
    }

    auto startTime = std::chrono::high_resolution_clock::now();

    std::vector<NumberProducts> products;
    std::tuple<int, int, NumberProducts::Direction> max{ -1, -1, NumberProducts::Direction::Diagonal }; // position in vector, value, direction

    int lineNum = numbers.size();
    int colNum = numbers[0].size();
    for (int rowNo = 0; rowNo < lineNum; ++rowNo)
    {
        for (int colNo = 0; colNo < colNum; ++ colNo)
        {
            NumberProducts number(numbers[rowNo][colNo], adjacentNumber);
            products.push_back(number);
            
            multiplyLeftNumbers(colNo, rowNo, colNum, number.getNumber(), products, max);
            multiplyAboveNumbers(colNo, rowNo, colNum, number.getNumber(), products, max);
            multiplyDiagonalNumbers(colNo, rowNo, colNum, number.getNumber(), products, max);
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();

    std::cout << test << "\n\n";
    std::cout << "Maximum product: " << std::get<1>(max)
        << "\nStarting from row #" << std::get<0>(max) / colNum + 1
        << " col #" << (std::get<0>(max) % colNum) + 1 << ' ' << adjacentNumber << " numbers "
        << (std::get<2>(max) == NumberProducts::Direction::Horizontal
                ? "to the right\n"
                : std::get<2>(max) == NumberProducts::Direction::Vertical
                    ? "down\n"
                    : "in the down-right diagonal\n\n");
    std::cout << "Time taken: " << ((endTime - startTime) / std::chrono::microseconds(1)) << " microseconds\n";

    return 0;
}