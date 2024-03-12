#include <vector>
#include <iostream>
#include <cassert>
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

/*
 * In-place sorting algorithms
 */
class Solution {
private:

    // HEAP SORT ////////////////////////////////////

    enum BubbleDown
    {
        BUBBLE_STOP,
        BUBBLE_LEFT,
        BUBBLE_RIGHT
    };

    template<typename T>
    static void bubbleDown(vector<T>& vec, size_t i, size_t n)
    {
        const size_t l = 2*i+1;
        const size_t r = 2*i+2;
        BubbleDown action = BUBBLE_STOP;
        if(l < n && vec[l] > vec[i])
        {
            action = BUBBLE_LEFT;
        }
        if(r < n && vec[r] > vec[i] && vec[r] > vec[l])
        {
            action = BUBBLE_RIGHT;
        }
        switch(action)
        {
            case BUBBLE_LEFT:
                std::swap(vec[i], vec[l]);
                bubbleDown(vec, l, n);
            break;
            case BUBBLE_RIGHT:
                std::swap(vec[i], vec[r]);
                bubbleDown(vec, r, n);
            break;
            default:break;
        }
    }

    template<typename T>
    static void heapify(vector<T>& vec)
    {
        size_t n = vec.size();
        size_t i = (n-1)/2; // nodes beyond this index have no children
        while(1)
        {
            // move [i] into the correct spot in the heap: [i+1...n)
            bubbleDown(vec, i, n);
            if(i==0)
                break;
            --i;
        }
    }

    template<typename T>
    static void heapSort(vector<T>& vec)
    {
        // algorithm will blow up with zero size
        if(vec.empty())
            return;

        // First step is to convert the vector into a max-heap ("heapify")
        // Properties of a max-heap:
        //  elem[0] is the largest value
        //  has a binary tree structure where every leaf node is smaller than it's parent / every parent is smaller than it's children.
        //  left child of [n] is [2n+1]
        //  right child of [n] is [2n+2]
        heapify(vec);

        // Next step:
        // remove largest element (elem[0])
        // swap it with the last element [i]
        // bubble the new root down to restore the heap property in [0..i)
        for(size_t i = vec.size()-1; i>0; --i)
        {
            T largest = vec[0];
            vec[0] = vec[i];
            bubbleDown(vec, 0, i);
            vec[i] = largest; 
        }
    }

    // QUICK SORT ////////////////////////////////////

    template<typename T>
    static void quickSort(const typename vector<T>::iterator& begin, const typename vector<T>::iterator& end)
    {
        // Choose a pivot p in the range [begin, end)
        // partition the elements such that all elements in [begin,p) are smaller than [p],
        // and all elements in (p, end) are larger than [p]
        auto sz = std::distance(begin,end);

        if(sz <= 1)
        {
            // base case : nothing to sort
            return;
        }

        if(sz == 2)
        {
            // base case for 2 elements : just swap if not in the correct order
            auto next = begin+1;
            if(*next < *begin)
            {
                std::swap(*next, *begin);
            }
            return;
        }

        // arbitrarily select the first element
        auto p = begin;
        T pivot = *p;
        // partition function : O(n)
        for(auto it=begin+1; it<end; ++it)
        {
            if(it > p && *it < pivot)
            {
                // element is smaller and on the wrong side of the pivot...
                // swap it with elements to the left until it's on the right side
                for(auto current=it; current>p; --current)
                {
                    auto prev = current-1;
                    std::swap(*current,*prev);
                }
                // pivot was swapped one place to the right
                ++p;
            }
        }

        // if left side is empty, move the pivot into it
        if(p == begin)
        {
            p = begin+1;
        }

        // sort the partitions
        quickSort<T>(begin, p);
        quickSort<T>(p, end);
    }

public:
    template<typename T>
    static void sort(vector<T>& vec)
    {
        quickSort<T>(vec.begin(), vec.end());
    }
};

int main(int argc, char *argv[])
{ 
    // Tests
    {
        vector<int> vec{};
        Solution solution{};
        solution.sort(vec);
        vector<int> expected{};
        std::cout << "expected: " << expected << " , actual: " << vec << std::endl;
        assert(std::equal(vec.begin(), vec.end(), expected.begin()));
    }
    {
        vector<int> vec{5};
        Solution solution{};
        solution.sort(vec);
        vector<int> expected{5};
        std::cout << "expected: " << expected << " , actual: " << vec << std::endl;
        assert(std::equal(vec.begin(), vec.end(), expected.begin()));
    }
    {
        vector<int> vec{3,2};
        Solution solution{};
        solution.sort(vec);
        vector<int> expected{2,3};
        std::cout << "expected: " << expected << " , actual: " << vec << std::endl;
        assert(std::equal(vec.begin(), vec.end(), expected.begin()));
    }
    {
        vector<int> vec{1,2,3};
        Solution solution{};
        solution.sort(vec);
        vector<int> expected{1,2,3};
        std::cout << "expected: " << expected << " , actual: " << vec << std::endl;
        assert(std::equal(vec.begin(), vec.end(), expected.begin()));
    }
    {
        vector<int> vec{3,2,1};
        Solution solution{};
        solution.sort(vec);
        vector<int> expected{1,2,3};
        std::cout << "expected: " << expected << " , actual: " << vec << std::endl;
        assert(std::equal(vec.begin(), vec.end(), expected.begin()));
    }
    {
        vector<int> vec{1,6,8,2,5,4,8,3,7};
        Solution solution{};
        solution.sort(vec);
        vector<int> expected{1,2,3,4,5,6,7,8,8};
        std::cout << "expected: " << expected << " , actual: " << vec << std::endl;
        assert(std::equal(vec.begin(), vec.end(), expected.begin()));
    }
    {
        vector<int> vec{19,30,-12,59,8,20,0,0,12,54,100,4213,5,33,0,23,45,16,5};
        Solution solution{};
        solution.sort(vec);
        vector<int> expected{-12,0,0,0,5,5,8,12,16,19,20,23,30,33,45,54,59,100,4213};
        std::cout << "expected: " << expected << " , actual: " << vec << std::endl;
        assert(std::equal(vec.begin(), vec.end(), expected.begin()));
    }
    return 0;
}