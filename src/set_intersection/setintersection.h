#pragma once

// STD
#include <optional>
#include <vector>

namespace SetIntersection
{
    std::vector<int> intersectKSortedSets(const std::vector<std::vector<int>> &sets)
    {
        const int n = sets.size();
        if (0 == n)
        {
            return {};
        }
        std::vector<int> index(n);
        std::vector<int> res{};
        int currMax = sets[0][0];
        int counter{};
        while (true)
        {
            bool isDone = false;
            std::optional<int> currMax = 0;
            int counter = 0;

            // Find the current max among the indices
            for (int i = 0; i < n; i++)
            {
                if (index[i] == sets[i].size())
                {
                    return res; // One list is exhausted, return result
                }

                if (not currMax.has_value() || sets[i][index[i]] > currMax.value())
                {
                    currMax = sets[i][index[i]];
                    counter = 1; // Reset counter for a new max
                }
                else if (sets[i][index[i]] == currMax)
                {
                    counter++;
                }
            }

            // If all arrays have the same current max, add it to the result
            if (counter == n)
            {
                res.push_back(currMax.value());
                for (int i = 0; i < n; i++)
                {
                    if (index[i] < sets[i].size() && sets[i][index[i]] == currMax)
                    {
                        index[i]++; // Move forward in each list that contained currMax
                    }
                }
            }
            else
            {
                // Advance pointers past elements < currMax
                for (int i = 0; i < n; i++)
                {
                    while (index[i] < sets[i].size() && sets[i][index[i]] < currMax)
                    {
                        index[i]++;
                    }
                }
            }
        }
        return {};
    }
};