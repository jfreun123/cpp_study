#include <vector>
#include <algorithm>

namespace PrimeHelpers
{
    std::vector<int> generateProducts(const std::vector<int> &primes)
    {
        std::vector<int> res{};
        const int n = primes.size();
        res.reserve((1 << n) - 1);
        auto dfs = [&](auto &&func, const int i) -> void
        {
            if (i == primes.size())
            {
                return;
            }

            func(func, i + 1);
            for (const int prod : res)
            {
                res.push_back(prod * primes[i]);
            }
            res.push_back(primes[i]);
        };
        dfs(dfs, 0);
        std::sort(res.begin(), res.end());
        return res;
    }

    std::vector<int> generateProductsClean(const std::vector<int> &primes)
    {
        std::vector<int> res{};
        const int n = primes.size();
        res.reserve((1 << n) - 1); // Corrected reserve size

        auto dfs = [&](auto &&func, const int i, const int product) -> void
        {
            if (i == n)
            {
                if (product != 1) // Exclude the empty product
                    res.push_back(product);
                return;
            }
            // Exclude current prime
            func(func, i + 1, product);
            // Include current prime
            func(func, i + 1, product * primes[i]);
        };

        dfs(dfs, 0, 1);
        std::sort(res.begin(), res.end());
        return res;
    }
}