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

/**
On each day, you may decide to buy and/or sell the stock.
You can only hold at most one share of the stock at any time. However, you can buy it then immediately sell it on the same day.
Find and return the maximum profit you can achieve.
*/
class Solution {
private:
        
    // i would use boost matrix or something but this is a toy problem
    template<typename T>
    class Matrix
    {
        private:
            T** m_pData;
            size_t m_N;
            size_t m_M;
        public:
            Matrix(const size_t n, const size_t m)
                : m_N(n)
                , m_M(m)
            {
                m_pData = new T*[n];
                for(int i=0; i<n; ++i)
                    m_pData[i] = new T[m];
            }
            Matrix(const size_t n)
                :Matrix(n,n)
            {
            }

            ~Matrix()
            {
                for(int i=0; i<m_N; ++i)
                    delete[] m_pData[i]; 
                delete[] m_pData;
            }

            // computers are good at copying, right? let's ignore move/reference semantics
            T get(size_t i, size_t j) const
            {
                return m_pData[i][j];
            }
            void set(size_t i, size_t j, T value)
            {
                m_pData[i][j] = value;
            }
    };

public:

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

   
    int maxProfit(vector<int>& prices) const
    {
        const size_t n = prices.size();
        
        Matrix<int> p(n); // reserves NxN heap
        p.set(0,0,0);

        vector<int> maxProfit;
        maxProfit.reserve(n);
        maxProfit[0] = 0;

        for(size_t x=1; x<n; ++x)
        {
            for(size_t y=0; y<x; ++y)
            {
                int profit = (prices[x] - prices[y]) + maxProfit[y];
                p.set(x,y, profit);
            }

            int max = maxProfit[x-1];
            for(size_t y=0; y<x; ++y)
            {
                max = std::max(max, p.get(x,y));
            }
            maxProfit[x] = max;
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
}
