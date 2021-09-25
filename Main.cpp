#include "NumberProducts.h"

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <chrono>

static const char* txt = "08 02 22 97 38 15 00 40 00 75 04 05 07 78 52 12 50 77 91 08\n"
                         "49 49 99 40 17 81 18 57 60 87 17 40 98 43 69 48 04 56 62 00\n"
                         "81 49 31 73 55 79 14 29 93 71 40 67 53 88 30 03 49 13 36 65\n"
                         "52 70 95 23 04 60 11 42 69 24 68 56 01 32 56 71 37 02 36 91\n"
                         "22 31 16 71 51 67 63 89 41 92 36 54 22 40 40 28 66 33 13 80\n"
                         "24 47 32 60 99 03 45 02 44 75 33 53 78 36 84 20 35 17 12 50\n"
                         "32 98 81 28 64 23 67 10 26 38 40 67 59 54 70 66 18 38 64 70\n"
                         "67 26 20 68 02 62 12 20 95 63 94 39 63 08 40 91 66 49 94 21\n"
                         "24 55 58 05 66 73 99 26 97 17 78 78 96 83 14 88 34 89 63 72\n"
                         "21 36 23 09 75 00 76 44 20 45 35 14 00 61 33 97 34 31 33 95\n"
                         "78 17 53 28 22 75 31 67 15 94 03 80 04 62 16 14 09 53 56 92\n"
                         "16 39 05 42 96 35 31 47 55 58 88 24 00 17 54 24 36 29 85 57\n"
                         "86 56 00 48 35 71 89 07 05 44 44 37 44 60 21 58 51 54 17 58\n"
                         "19 80 81 68 05 94 47 69 28 73 92 13 86 52 17 77 04 89 55 40\n"
                         "04 52 08 83 97 35 99 16 07 97 57 32 16 26 26 79 33 27 98 66\n"
                         "88 36 68 87 57 62 20 72 03 46 33 67 46 55 12 32 63 93 53 69\n"
                         "04 42 16 73 38 25 39 11 24 94 72 18 08 46 29 32 40 62 76 36\n"
                         "20 69 36 41 72 30 23 88 34 62 99 69 82 67 59 85 74 04 36 16\n"
                         "20 73 35 29 78 31 90 01 74 31 49 71 48 86 81 16 23 57 05 54\n"
                         "01 70 54 71 83 51 54 69 16 92 33 48 61 43 52 01 89 19 67 48";
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

// multiply up-left diagonal numbers
void multiplyRightDiagonalNumbers(int colNo, int rowNo, int colNum, int factor,
    std::vector<NumberProducts>& products,
    std::tuple<int, int, NumberProducts::Direction>& max)
{
    for (int prevRow = rowNo - 1, prevCol = colNo - 1; prevRow >= 0 && prevCol >= 0; --prevRow, -- prevCol)
    {
        int prevPosition = prevRow * colNum + prevCol;
        auto multiplicationResult = products[prevPosition].addRightDiagonalFactor(factor);
        if (multiplicationResult.second == -1)
        {
            // all previous numbers up were multiplied
            break;
        }

        if (multiplicationResult.second == adjacentNumber
            && std::get<1>(max) < multiplicationResult.first)
        {
            // set new maximum
            max = { prevPosition, multiplicationResult.first, NumberProducts::Direction::RightDiagonal };
        }
    }
}

// multiply up-right diagonal numbers
void multiplyLeftDiagonalNumbers(int colNo, int rowNo, int colNum, int factor,
    std::vector<NumberProducts>& products,
    std::tuple<int, int, NumberProducts::Direction>& max)
{
    for (int prevRow = rowNo - 1, prevCol = colNo + 1; prevRow >= 0 && prevCol < colNum; --prevRow, ++prevCol)
    {
        int prevPosition = prevRow * colNum + prevCol;
        auto multiplicationResult = products[prevPosition].addLeftDiagonalFactor(factor);
        if (multiplicationResult.second == -1)
        {
            // all previous numbers up were multiplied
            break;
        }

        if (multiplicationResult.second == adjacentNumber
            && std::get<1>(max) < multiplicationResult.first)
        {
            // set new maximum
            max = { prevPosition, multiplicationResult.first, NumberProducts::Direction::LeftDiagonal };
        }
    }
}

int main()
{
    std::vector<std::vector<int>> numbers = parseNumberString(txt);
    if (numbers.empty())
    {
        std::cout << "Illegal numbers string";
        return 0;
    }

    auto startTime = std::chrono::high_resolution_clock::now();

    std::vector<NumberProducts> products;
    std::tuple<int, int, NumberProducts::Direction> max{ -1, -1, NumberProducts::Direction::RightDiagonal }; // position in vector, value, direction

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
            multiplyRightDiagonalNumbers(colNo, rowNo, colNum, number.getNumber(), products, max);
            multiplyLeftDiagonalNumbers(colNo, rowNo, colNum, number.getNumber(), products, max);
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();

    std::cout << txt << "\n\n";
    std::cout << "Maximum product: " << std::get<1>(max)
        << "\nStarting from row #" << std::get<0>(max) / colNum + 1
        << " col #" << (std::get<0>(max) % colNum) + 1 << ' ' << adjacentNumber << " numbers "
        << (std::get<2>(max) == NumberProducts::Direction::Horizontal
                ? "to the right\n"
                : std::get<2>(max) == NumberProducts::Direction::Vertical
                    ? "down\n"
                    : std::get<2>(max) == NumberProducts::Direction::RightDiagonal
                        ? "in the down-right diagonal\n"
                        : "in the down-left diagonal\n\n");
    std::cout << "Time taken: " << ((endTime - startTime) / std::chrono::microseconds(1)) << " microseconds\n";

    return 0;
}