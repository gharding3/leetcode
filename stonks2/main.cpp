#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// helper to print vec
template<typename T>
ostream& operator<<(ostream& os, const vector<T>& vec)
{
    bool first = true;
    std::cout << "[";
    for(auto& elem : vec)
    {
        if(!first)
            std::cout << ",";
        std::cout << elem;
        first = false;
    }
    std::cout << "]";
    return os;
}

/*
    On each day, you may decide to buy and/or sell the stock.
    You can only hold at most one share of the stock at any time. However, you can buy it then immediately sell it on the same day.
    Find and return the maximum profit you can achieve.
*/

/*
    Dynamic programming with O(n^2) space, O(n) time
    keep track of p[x,y]
    where x = current day,
    y = day stock was last purchased

    another array maxProfit[3] -> max profit earnable up to this day (subproblem)
    maxProfit[x] = the maximum of any column of p(x,y)

    p[0,0] = 0
    maxProfit(0) = 0

    p[1,0] = (price[1] - price[0]) + maxProfit[0] // transaction + previous returns
    p[1,1] = maxProfit[0] // no transaction
    maxProfit(1) = MAX(p[1,0], p[1,1])

    p[2,0] = (price[2] - price[0]) + maxProfit(0)
    p[2,1] = (price[2] - price[1]) + maxProfit(1)
    p[2,2] = maxProfit[1] // no transaction
    maxProfit(1) = MAX(p[2,0], p[2,1], p[2,2])

    and so on...
*/

class Solution {
public:
    int maxProfit(vector<int>& prices) const
    {
        const size_t n = prices.size();

        int profitIfWeSellToday = 0;
        int maxProfitToday = 0;

        vector<int> maxProfit(n);
        maxProfit[0] = 0;

        for(size_t x=1; x<n; ++x)
        {
            maxProfitToday = maxProfit[x-1];

            for(size_t y=0; y<x; ++y)
            {
                profitIfWeSellToday = (prices[x] - prices[y]) + maxProfit[y];
                if(profitIfWeSellToday > maxProfitToday)
                {
                    maxProfitToday = profitIfWeSellToday;
                }
            }

            maxProfit[x] = maxProfitToday;
        }

        return maxProfit[n-1];
    }
};


int main(int argc, char *argv[])
{ 
    // Tests
    {
        vector<int> prices{7,1,5,3,6,4};
        Solution solution{};
        int actual = solution.maxProfit(prices);
        int expected = 7;
        std::cout << "expected: " << expected << ", actual: " << actual << std::endl;
        assert(expected == actual);
    }
    {
        vector<int> prices{1,2,3,4,5};
        Solution solution{};
        int actual = solution.maxProfit(prices);
        int expected = 4;
        std::cout << "expected: " << expected << ", actual: " << actual << std::endl;
        assert(expected == actual);
    }
    {
        vector<int> prices{7,6,4,3,1};
        Solution solution{};
        int actual = solution.maxProfit(prices);
        int expected = 0;
        std::cout << "expected: " << expected << ", actual: " << actual << std::endl;
        assert(expected == actual);
    }
    {
        vector<int> prices{1,4,3,6};
        Solution solution{};
        int actual = solution.maxProfit(prices);
        int expected = 6;
        std::cout << "expected: " << expected << ", actual: " << actual << std::endl;
        assert(expected == actual);
    }
    {
        vector<int> prices{1,2945,9,243,0,23,122,8903,3234,392,733,2222,3332,4444,5555,6666,1111};
        Solution solution{};
        int actual = solution.maxProfit(prices);
        int expected = 18355;
        std::cout << "expected: " << expected << ", actual: " << actual << std::endl;
        assert(expected == actual);
    }
    {
        vector<int> prices{3,4,5};
        Solution solution{};
        int actual = solution.maxProfit(prices);
        int expected = 2;
        std::cout << "expected: " << expected << ", actual: " << actual << std::endl;
        assert(expected == actual);
    }
        {
        vector<int> prices{121,120,119};
        Solution solution{};
        int actual = solution.maxProfit(prices);
        int expected = 0;
        std::cout << "expected: " << expected << ", actual: " << actual << std::endl;
        assert(expected == actual);
    }
    {
        vector<int> prices{100000};
        Solution solution{};
        int actual = solution.maxProfit(prices);
        int expected = 0;
        std::cout << "expected: " << expected << ", actual: " << actual << std::endl;
        assert(expected == actual);
    }
    {
        vector<int> prices{43,23,46,23,40,30,30,57,23};
        Solution solution{};
        int actual = solution.maxProfit(prices);
        int expected = 67;
        std::cout << "expected: " << expected << ", actual: " << actual << std::endl;
        assert(expected == actual);
    }
}
