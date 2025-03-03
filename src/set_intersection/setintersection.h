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
            bool isDoneAfterLevel = false;
            for (int i{}; i < n; i++)
            {
                // update the indexs
                while (index[i] < sets[i].size() && sets[i][index[i]] < currMax)
                {
                    index[i]++;
                }

                if (sets[i][index[i]] == currMax)
                {
                    counter++;
                    if (counter == n)
                    {
                        index[i]++;
                        res.push_back(currMax);
                    }
                }
                else if (sets[i][index[i]] > currMax)
                {
                    currMax = sets[i][index[i]];
                    counter = 1;
                    index[i]++;
                }

                if (index[i] == sets[i].size())
                {
                    isDoneAfterLevel = true;
                }
            }

            if (isDoneAfterLevel)
            {
                return res;
            }
        }
        return {};
    }
};