#include <iostream>
#include <string>
#include <cassert>
#include <vector>

using namespace std;


class Solution {
    
    enum Direction
    {
        Left,
        Right,
        Up,
        Down
    };

public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) 
    {
        vector<int> result{};
        Direction dir = Direction::Right;
        
        int deadzone_left = 0;
        int deadzone_right = 0;
        int deadzone_top = 0;
        int deadzone_bottom = 0;

        bool finished = false;

        // early termination cases
        // assume square matrix
        const int height = matrix.size();
        if(height == 0)
            return result;
        const int width = matrix[0].size();
        if(width == 0)
            return result;

        int i = 0;
        int j = 0;
        while(j >= deadzone_left && j < (width - deadzone_right)
            && i >= deadzone_top && i < (height - deadzone_bottom))
        {
            result.push_back(matrix[i][j]);

            switch(dir)
            {
                case Direction::Right:
                {
                    ++j;
                    if(j >= (width - deadzone_right))
                    {
                        ++i;
                        --j;
                        ++deadzone_top;
                        dir = Direction::Down;
                    }
                }
                break;
                case Direction::Down:
                {
                    ++i;
                    if(i >= (height - deadzone_bottom))
                    {
                        --i;
                        --j;
                        ++deadzone_right;
                        dir = Direction::Left;
                    }
                }
                break;
                case Direction::Left:
                {
                    --j;
                    if(j < (0 + deadzone_left))
                    {
                        --i;
                        ++j;
                        ++deadzone_bottom;
                        dir = Direction::Up;
                    }
                }
                break;
                case Direction::Up:
                {
                    --i;
                    if(i < (0 + deadzone_top))
                    {
                        ++i;
                        ++j;
                        ++deadzone_left;
                        dir = Direction::Right;
                    }
                }
                break;
                default:break;
            }
        }
        
        return result;
    }
};

std::ostream& operator<<(std::ostream& os, std::vector<int> vec)
{
    os << "[";
    bool first = true;
    for(auto& elem : vec)
    {
        if(!first)
            os << ", ";
        os << elem;
        first = false;
    }
    os << "]";
    return os;
}

int main(int argc, char *argv[])
{
    {
        Solution solution{};
        vector<vector<int>> matrix = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
        vector<int> actual = solution.spiralOrder(matrix);
        vector<int> expected = {1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7};
        std::cout << "actual = " << actual << std::endl;
        std::cout << "expected = " << expected << std::endl;
        assert(actual == expected);
    }

    {
        Solution solution{};
        vector<vector<int>> matrix = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
        vector<int> actual = solution.spiralOrder(matrix);
        vector<int> expected = {1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10};
        std::cout << "actual = " << actual << std::endl;
        std::cout << "expected = " << expected << std::endl;
        assert(actual == expected);
    }

    {
        Solution solution{};
        vector<vector<int>> matrix = {{1, 2}, {5, 6}, {9, 10}};
        vector<int> actual = solution.spiralOrder(matrix);
        vector<int> expected = {1, 2, 6, 10, 9, 5};
        std::cout << "actual = " << actual << std::endl;
        std::cout << "expected = " << expected << std::endl;
        assert(actual == expected);
    }

    {
        Solution solution{};
        vector<vector<int>> matrix = {{1}, {5}, {9}};
        vector<int> actual = solution.spiralOrder(matrix);
        vector<int> expected = {1, 5, 9};
        std::cout << "actual = " << actual << std::endl;
        std::cout << "expected = " << expected << std::endl;
        assert(actual == expected);
    }

    {
        Solution solution{};
        vector<vector<int>> matrix = {{1, 2, 3}};
        vector<int> actual = solution.spiralOrder(matrix);
        vector<int> expected = {1, 2, 3};
        std::cout << "actual = " << actual << std::endl;
        std::cout << "expected = " << expected << std::endl;
        assert(actual == expected);
    }

    {
        Solution solution{};
        vector<vector<int>> matrix = {};
        vector<int> actual = solution.spiralOrder(matrix);
        vector<int> expected = {};
        std::cout << "actual = " << actual << std::endl;
        std::cout << "expected = " << expected << std::endl;
        assert(actual == expected);
    }

    return 0;
}