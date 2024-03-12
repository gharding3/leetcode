#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

/**
You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.
Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.
*/
class Solution {
public:

    /*
    O(n) strategy
    Iterate backwards in time.
    Keep track of the highest price seen so far (maxPrice).
    If we are below maxPrice, calculate profit.
    Keep track of the best profit as we go.
    */
    int maxProfit(vector<int>& prices) const
    {
        const size_t n = prices.size();
        int maxPrice = 0;
        int maxProfit = 0;

        for(auto it=prices.rbegin(); it != prices.rend(); ++it)
        {
            int price=*it;
            if(price > maxPrice)
            {
                maxPrice = price;
            }
            else // price <= maxPrice
            {
                int profit = maxPrice - price;
                if(profit > maxProfit)
                    maxProfit = profit;
            }
        }

        return maxProfit;
    }
};


int main(int argc, char *argv[])
{ 
    // Tests
    {
        vector<int> prices{1,8,6,2,5,4,8,3,7};
        Solution solution{};
        int actual = solution.maxProfit(prices);
        int expected = 7;
        assert(expected == actual);
    }
    {
        vector<int> prices{100,83,64,20,67,94,98,30,75};
        Solution solution{};
        int actual = solution.maxProfit(prices);
        int expected = 78;
        assert(expected == actual);
    }
    {
        vector<int> prices{7,1,5,3,6,4};
        Solution solution{};
        int actual = solution.maxProfit(prices);
        int expected = 5;
        assert(expected == actual);
    }
    {
        vector<int> prices{};
        Solution solution{};
        int actual = solution.maxProfit(prices);
        int expected = 0;
        assert(expected == actual);
    }
    {
        vector<int> prices{1};
        Solution solution{};
        int actual = solution.maxProfit(prices);
        int expected = 0;
        assert(expected == actual);
    }
    {
        vector<int> prices{1,2,3,4,5,6};
        Solution solution{};
        int actual = solution.maxProfit(prices);
        int expected = 5;
        assert(expected == actual);
    }
    {
        vector<int> prices{10,8,6,4,2};
        Solution solution{};
        int actual = solution.maxProfit(prices);
        int expected = 0;
        assert(expected == actual);
    }
    {
        vector<int> prices{7,6,4,3,1};
        Solution solution{};
        int actual = solution.maxProfit(prices);
        int expected = 0;
        assert(expected == actual);
    }
}
