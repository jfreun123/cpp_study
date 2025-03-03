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
                // "remove" dumb indecies.  These will never have an intersection.
                //  note:  an if statement here is not enough. Need an if statement.
                //  This is so that the next time we process set i-1 we can be sure
                //  of intersection.
                while (index[i] < sets[i].size() && sets[i][index[i]] < currMax)
                {
                    index[i]++;
                }

                //  return if we are done.
                if (index[i] == sets[i].size())
                {
                    return res;
                }

                //  if we see our max:
                //  update the counter and move on
                if (sets[i][index[i]] == currMax)
                {
                    counter++;
                    index[i]++;
                    if (counter == n)
                    {
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