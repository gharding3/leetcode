#include <vector>
#include <iostream>
#include <cassert>
#include <array>
#include <algorithm>

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

class Solution {
private:

public:
    
    int maxArea(vector<int>& height) 
    {
        size_t maxArea = 0;
        size_t n = height.size();
        if(n < 2)
        {
            // invalid arguments
            return -1;
        }

        // TWO-POINTER SOLUTION:
        // Set L to the first wall
        // Set R to the last wall
        // Calculate the area
        // We can shift either pointer to check if this increases the bucket size
        // If (L < R), then it makes sense to shift L (increase it)
        // otherwise shift R
        // we still need to iterate over all N walls, in case the middle ones are very tall
        size_t left = 0;
        size_t right = n-1;

        size_t area;
        while(left < right)
        {
            area = (right - left) * std::min(height[left], height[right]);
            if(area > maxArea)
                maxArea = area;
            if(height[left] < height[right])
            {
                ++left;
            }
            else
            {
                --right;
            }
        }

        return static_cast<int>(maxArea);
    }
};

int main(int argc, char *argv[])
{ 
    // Tests
    {
        vector<int> walls{1,8,6,2,5,4,8,3,7};
        Solution solution{};
        int actual = solution.maxArea(walls);
        int expected = 49; // 7 buckets of height 7
        assert(expected == actual);
    }
    {
        vector<int> walls{1,1};
        Solution solution{};
        int actual = solution.maxArea(walls);
        int expected = 1; // 1 bucket of height 1
        assert(expected == actual);
    }
    {
        vector<int> walls{1,2,3};
        Solution solution{};
        int actual = solution.maxArea(walls);
        int expected = 2; //1 bucket of height 2
        assert(expected == actual);
    }
    {
        vector<int> walls{1,3,5,20,1,20,6,5,2};
        Solution solution{};
        int actual = solution.maxArea(walls);
        int expected = 40; // middle bucket of height 40
        assert(expected == actual);
    }
    {
        vector<int> walls{1,3,5,20,1,20,6,5,2};
        Solution solution{};
        int actual = solution.maxArea(walls);
        int expected = 40; // middle bucket of height 40
        assert(expected == actual);
    }
    return 0;
}