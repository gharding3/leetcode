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
private:

    // TODO: Use std::span with C++20
    template<typename T>
    class VectorSpan
    {
    private:
        const typename vector<T>::iterator m_begin;
        const typename vector<T>::iterator m_end;

    public:

        VectorSpan(typename vector<T>::iterator begin, typename vector<T>::iterator end)
            : m_begin(begin)
            , m_end(end)
        {
        }
        VectorSpan(vector<T>& source)
            : VectorSpan(source.begin(), source.end())
        {
        }

        int size() const
        {
            return std::distance(m_begin, m_end);
        }
        T operator[](int i) const
        {
            return *(m_begin + i);
        }
        const typename vector<T>::iterator& begin() const
        {
            return m_begin;
        }
        const typename vector<T>::iterator& end() const
        {
            return m_end;
        }
    };

public:

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) 
    {
        VectorSpan<int> span1(nums1);
        VectorSpan<int> span2(nums2);
        return findMedianSortedArraysRecursive(span1, span2);
    }

private:

    double findMedian(const VectorSpan<int>& nums) const
    {
        size_t sz = nums.size();
        assert(sz > 0);
        if(sz % 2 == 0)
        {
            return (nums[sz/2] + nums[sz/2 - 1]) / 2.0;
        }
        else
        {
            return nums[sz/2];
        }
    }

    // helper for base case: find median of a vector plus an additional element
    double findMedian(const VectorSpan<int>& nums, int c) const
    {
        size_t sz = nums.size();
        if(sz == 1)
        {
            return (nums[0] + c) / 2.0;
        }
        int a = nums[sz/2 - 1];
        int b = nums[sz/2];
        if(sz % 2 == 0)
        {
            // combined size is odd
            return (c < a) ? a : (c > b) ? b : c;
        }
        else
        {
            // combined size is even
            if(c < a)
            {
                return (a + b) / 2.0;
            }
            else if(c > b)
            {
                return (b + c) / 2.0;
            }
            else
            {
                return (a + c) / 2.0;
            }
        }
    }

    double findMedianSortedArraysRecursive(const VectorSpan<int>& nums1, const VectorSpan<int>& nums2) const
    {
        // ensure first collection is smaller
        size_t size1 = nums1.size();
        size_t size2 = nums2.size();
        if(size2 < size1)
        {
            return findMedianSortedArraysRecursive(nums2, nums1);
        }
        
        // base case
        if(size1 == 1)
        {
            return findMedian(nums2, nums1[0]);
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
                int k = size2 - removed;

                VectorSpan<int> numParts1(nums1.begin() + j, nums1.end());
                VectorSpan<int> numParts2(nums2.begin(), nums2.begin() + k);
                return findMedianSortedArraysRecursive(numParts1, numParts2);
            }
            else // m1 > m2
            {
                // search [l..M][0..i]
                int i = (size1 %2 == 0) ? size1/2 : size1/2 + 1;
                int removed = (size1 - i);
                int l = removed;

                VectorSpan<int> numParts1(nums2.begin() + l, nums2.end());
                VectorSpan<int> numParts2(nums1.begin(), nums1.begin() + i);
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
        double actual = solution.findMedianSortedArrays(nums1, nums2);
        double expected = 1;
        std::cout << "expected: " << expected << ", actual: " << actual << std::endl;
        assert(actual == expected);
    }
    {
        std::vector<int> nums1{3};
        std::vector<int> nums2{4};
        Solution solution{};
        double actual = solution.findMedianSortedArrays(nums1, nums2);
        double expected = 3.5;
        std::cout << "expected: " << expected << ", actual: " << actual << std::endl;
        assert(actual == expected);
    }
    {
        std::vector<int> nums1{1,3,5,7,9};
        std::vector<int> nums2{0,2,4,6,8};
        Solution solution{};
        double actual = solution.findMedianSortedArrays(nums1, nums2);
        double expected = 4.5;
        std::cout << "expected: " << expected << ", actual: " << actual << std::endl;
        assert(actual == expected);
    }
    {
        std::vector<int> nums1{10,10,20,20,30,30,100};
        std::vector<int> nums2{15,25,35,45};
        // {10,10,15,20,20 25 30,30,35,45,100}
        Solution solution{};
        double actual = solution.findMedianSortedArrays(nums1, nums2);
        double expected = 25;
        std::cout << "expected: " << expected << ", actual: " << actual << std::endl;
        assert(actual == expected);
    }
    {
        std::vector<int> nums1{1,2};
        std::vector<int> nums2{3,4};
        Solution solution{};
        double actual = solution.findMedianSortedArrays(nums1, nums2);
        double expected = 2.5;
        std::cout << "expected: " << expected << ", actual: " << actual << std::endl;
        assert(actual == expected);
    }
    {
        std::vector<int> nums1{10,10,20,20,30,30,100};
        std::vector<int> nums2{15,25,35};
        // {10,10,15,20,20, 25,30,30,35,100}
        Solution solution{};
        double actual = solution.findMedianSortedArrays(nums1, nums2);
        double expected = 22.5;
        std::cout << "expected: " << expected << ", actual: " << actual << std::endl;
        assert(actual == expected);
    }
}