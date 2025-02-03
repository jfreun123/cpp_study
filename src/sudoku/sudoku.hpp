// STD
#include <bitset>
#include <cassert>
#include <execution>
#include <iostream>
#include <optional>
#include <ranges>
#include <unordered_set>
#include <vector>

constexpr int size = 9;
constexpr int numberOfIntegers = 10; // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
namespace Sudoku
{
    using OptionalSudokuSolution = std::optional<std::vector<std::vector<char>>>;
    class Solution
    {
    public:
        OptionalSudokuSolution getSudokuSolutionUnused(std::vector<std::vector<char>> board, const int notUsedNumber, const int minRequiredGCD)
        {
            std::bitset<numberOfIntegers> rowMask[size]{}, colMask[size]{}, blockMask[size]{};
            std::vector<std::pair<int, int>> emptyCells{};
            std::vector<std::vector<char>> solution{};
            // Precompute existing numbers and track empty cells
            for (int r = 0; r < size; ++r)
            {
                for (int c = 0; c < size; ++c)
                {
                    if (board[r][c] != '.')
                    {
                        const int num = board[r][c] - '0';
                        if (num == notUsedNumber)
                        {
                            return std::nullopt;
                        }
                        rowMask[r].set(num);
                        colMask[c].set(num);
                        blockMask[(r / 3) * 3 + (c / 3)].set(num);
                    }
                    else
                    {
                        emptyCells.emplace_back(r, c);
                    }
                }
            }

            // Solve via optimized backtracking
            std::optional<int> currGCD{};
            std::optional<int> maxGCDSeen{};

            auto updateGCD = [&](const int idx)
            {
                const auto [row, col] = emptyCells[idx];
                if (0 == idx) [[unlikely]]
                {
                    assert(row == 0);
                    return;
                }

                // If I placed down the last cell, update the last row
                if ((idx + 1) == emptyCells.size()) [[unlikely]]
                {
                    assert(row == (size - 1));
                    assert(currGCD.has_value());
                    currGCD = std::gcd(currGCD.value(), rowToInt(board[row]));
                    return;
                }

                const auto [prevRow, prevCol] = emptyCells[idx - 1];

                if (row == prevRow)
                {
                    return;
                }

                const int prevRowAsInt = rowToInt(board[prevRow]);
                if (not currGCD.has_value()) [[unlikely]]
                {
                    currGCD = prevRowAsInt;
                    return;
                }
                assert((row - prevRow) == 1);
                currGCD = std::gcd(currGCD.value(), prevRowAsInt);
            };

            auto backtrack = [&](auto &&func, const int idx)
            {
                // stop if it is too small and if it less than the largest
                if (currGCD.has_value() && (currGCD < minRequiredGCD || (maxGCDSeen.has_value() && (currGCD <= maxGCDSeen))))
                {
                    return;
                }

                if (idx == emptyCells.size())
                {
                    solution = board;
                    assert(currGCD.has_value());
                    maxGCDSeen = std::max(maxGCDSeen.value_or(0), currGCD.value());
                    assert(currGCD == computeBoardGCD(board));
                    std::cout << "Curr GCD " << currGCD.value() << std::endl;
                    std::cout << "Max GCD " << maxGCDSeen.value() << std::endl;
                    return;
                }

                const auto [row, col] = emptyCells[idx];

                int blockIdx = (row / 3) * 3 + (col / 3);

                for (int num = 0; num < numberOfIntegers; ++num)
                {
                    if (notUsedNumber != num && !rowMask[row][num] && !colMask[col][num] && !blockMask[blockIdx][num])
                    {
                        // Storage for later
                        const auto prevGCD = currGCD;

                        // Place number
                        board[row][col] = num + '0';
                        rowMask[row].set(num);
                        colMask[col].set(num);
                        blockMask[blockIdx].set(num);
                        updateGCD(idx);

                        func(func, idx + 1);

                        // Undo choice
                        board[row][col] = '.';
                        rowMask[row].reset(num);
                        colMask[col].reset(num);
                        blockMask[blockIdx].reset(num);
                        currGCD = prevGCD;
                    }
                }
            };

            backtrack(backtrack, 0);
            if (solution.empty())
            {
                return std::nullopt;
            }
            printBoard(board);
            return solution;
        }

        void printBoard(const std::vector<std::vector<char>> &board)
        {
            std::cout << " ============ BOARD ============ " << std::endl;
            for (const auto &row : board)
            {
                for (const auto &value : row)
                {
                    std::cout << value << "";
                }
                std::cout << std::endl;
            }
        }

    private:
        int rowToInt(const std::vector<char> &row)
        {
            std::string asStr(row.cbegin(), row.cend());
            return std::stoi(asStr);
        }

        int computeBoardGCD(const std::vector<std::vector<char>> &board)
        {
            auto getGCDOfVerctor = [](const std::vector<int> rows) -> int
            {
                return std::accumulate(rows.begin(), rows.end(), rows[0], std::gcd<int, int>);
            };

            auto convertToVectorInt = [this](const std::vector<std::vector<char>> &board)
            {
                std::vector<int> res{};
                res.reserve(board.size());
                for (const auto &row : board)
                {
                    res.emplace_back(rowToInt(row));
                }
                return res;
            };

            return getGCDOfVerctor(convertToVectorInt(board));
        }
    };
}
