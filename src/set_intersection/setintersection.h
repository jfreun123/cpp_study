#pragma once

// STD
#include <vector>

namespace SetIntersection
{
    static std::vector<int> intersectKSortedSets(const std::vector<std::vector<int>> &sets)
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
            for (int i{}; i < n; i++)
            {
                // empty list found we can just return
                if (index[i] == sets[i].size())
                {
                    return res;
                }

                // "remove" dumb indecies.  These will never have an intersection.
                while (index[i] < sets[i].size() && sets[i][index[i]] < currMax)
                {
                    index[i]++;
                }

                if (sets[i][index[i]] == currMax)
                {
                    counter++;
                    if (counter == n)
                    {
                        // everyone can take a step together
                        for (int j{}; j < n; j++)
                        {
                            index[j]++;
                        }
                        res.push_back(currMax);
                    }
                }
                else if (sets[i][index[i]] > currMax)
                {
                    currMax = sets[i][index[i]];
                    counter = 1;
                    index[i]++;
                }
            }
        }
        return {};
    }
};