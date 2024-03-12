#include <vector>
#include <cmath>
#include <iostream>
#include <cassert>

using namespace std;

// median : middle value of a collection
// has same number of elements less than as greater than

// naive idea: merge the sorted arrays (requires space allocation)
// into another sorted container
// then get the middle element of that container
// if N % 2 = 0 then M = (elems[N/2] + elems[N/2 - 1])/2
// if N % 2 == 1 then M = elems[N/2] (integer floor)
// runtime complexity is O(m + n)
// space complexity is O(m + n)
    
// optim: we can reduce the space complexity to O((m+n)/2) by only merging the first half the merged collection
// since this is all we need to get the median
// optim: we can use pointers to the tails of A and B as we are merging,
// instead of allocating a "real" container to store them.
// stop when the two pointers have traversed (n+m)/2 elements.

// O(log(n+m)) method: use binary search ("divide and conquer")
// take the medians of A and B : m1 and m2 respectively
// consider the parts:  
//      A: [0..i] m1 [j..N]      (if N is odd)
//      B: [0..k] m2 [l..M]      (if M is odd)
// or:
//      A: [0..i][j..N]          (if N is even)
//      B: [0..k][l..M]          (if M is even)
// 
// let P = sizeof([0..i]) = sizeof([j..N])  (by definition of median)
// let Q = sizeof([0..k]) = sizeof([k..M])  ("")
// 
// if(m1 < m2),
//  we can then search for the median in [j..N][0..k]
//  since the true median is somewhere between (m1, m2)
//
// if(m1 > m2)
//  we can then search for the median in [l..M][0..i]
//  since the true median is somewhere beteen (m2, m1)

class Solution {

    size_t m_totalSize = 0;

public:

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) 
    {
        size_t size1 = nums1.size();
        size_t size2 = nums2.size();
        m_totalSize = size1 + size2;
        return findMedianSortedArraysRecursive(nums1, nums2);
    }

private:

    int findMedian(vector<int>& nums) const
    {
        size_t sz = nums.size();
        assert(sz > 0);
        if(sz % 2 == 0)
        {
            return (nums.at(sz/2) + nums.at(sz/2 - 1)) / 2;
        }
        else
        {
            return nums.at(sz/2);
        }
    }

    double findMedianSortedArraysRecursive(vector<int>& nums1, vector<int>& nums2) const
    {
        // ensure first collection is smaller
        size_t size1 = nums1.size();
        size_t size2 = nums2.size();
        if(size2 < size1)
            return findMedianSortedArraysRecursive(nums2, nums1);

        // base case
        if(size1 == 0)
        {
            return findMedian(nums2);
        }
        else if(size1 == 1 && size2 == 1)
        {
            return (m_totalSize % 2 == 0)
                ? (nums1[0] + nums2[0]) / 2
                : std::min(nums1[0], nums2[0]);
        }

        {
            // split both sides
            int m1 = findMedian(nums1);
            int m2 = findMedian(nums2);
            if(m1 == m2)
            {
                return m1;
            }
            else if(m1 < m2)
            {
                // search [j..N][0..k]
                int j = (size1 % 2 == 0) ? size1/2 : size1/2 + 1;
                int removed = j;
                int k = size2 - removed; // remove at most j from the bigger collection

                // TODO: find way to use ranges/spans in C++
                // instead of allocating more vectors
                std::vector<int> numParts1{}, numParts2{};
                std::copy(nums1.begin() + j, nums1.end(), std::back_inserter(numParts1));
                std::copy(nums2.begin(), nums2.begin() + k, std::back_inserter(numParts2));
                return findMedianSortedArraysRecursive(numParts1, numParts2);
            }
            else // m1 > m2
            {
                // search [l..M][0..i]
                int i = size1/2;
                int removed = (size1 - i);
                int l = removed; // remove at most i from the bigger collection

                // TODO: find way to use ranges/spans in C++
                // instead of allocating more vectors
                std::vector<int> numParts1{}, numParts2{};
                std::copy(nums2.begin() + l, nums2.end(), std::back_inserter(numParts1));
                std::copy(nums1.begin(), nums1.begin() + i, std::back_inserter(numParts2));
                return findMedianSortedArraysRecursive(numParts1, numParts2);
            }
        }
    }
};

int main(int argc, char *argv[])
{
    {
        std::vector<int> nums1{0};
        std::vector<int> nums2{1,5};
        Solution solution{};
        int actual = solution.findMedianSortedArrays(nums1, nums2);
        int expected = 1;
        std::cout << "expected: " << expected << ", actual: " << actual << std::endl;
        assert(actual == expected);
    }
    {
        std::vector<int> nums1{3};
        std::vector<int> nums2{4};
        Solution solution{};
        int actual = solution.findMedianSortedArrays(nums1, nums2);
        int expected = 3;
        std::cout << "expected: " << expected << ", actual: " << actual << std::endl;
        assert(actual == expected);
    }
    {
        std::vector<int> nums1{1,3,5,7,9};
        std::vector<int> nums2{0,2,4,6,8};
        Solution solution{};
        int actual = solution.findMedianSortedArrays(nums1, nums2);
        int expected = 4;
        std::cout << "expected: " << expected << ", actual: " << actual << std::endl;
        assert(actual == expected);
    }
    {
        std::vector<int> nums1{10,10,20,20,30,30,100};
        std::vector<int> nums2{15,25,35,45};
        // {10,10,15,20,20 25 30,30,35,45,100}
        Solution solution{};
        int actual = solution.findMedianSortedArrays(nums1, nums2);
        int expected = 25;
        std::cout << "expected: " << expected << ", actual: " << actual << std::endl;
        assert(actual == expected);
    }
    {
        // TODO: DEBUG
        std::vector<int> nums1{10,10,20,20,30,30,100};
        std::vector<int> nums2{15,25,35};
        // {10,10,15,20,20, 25,30,30,35,100}
        Solution solution{};
        int actual = solution.findMedianSortedArrays(nums1, nums2);
        int expected = 22;
        std::cout << "expected: " << expected << ", actual: " << actual << std::endl;
        assert(actual == expected);
    }
}