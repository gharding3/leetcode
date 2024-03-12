#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:

    struct Cell
    {
        int score = 0;
        int* pond = nullptr;
    };

    int findMaxFish(vector<vector<int>>& grid)
    {
        // edge cases
        size_t height = grid.size();
        if(height == 0)
            return 0;
        size_t width = grid[0].size();
        if(width == 0)
            return 0;

        // create a solution grid with same dimensions
        Cell no_fish{};
        vector<vector<Cell>> cells(height, std::vector<Cell>(width, no_fish));

        // keep track of best score
        int bestScore = 0;

        // visit every cell
        for(size_t i=0; i < height; ++i)
        {
            for(size_t j=0; j < width; ++j)
            {
                int fish = grid[i][j];
                Cell& cell = cells[i][j];

                if(fish > 0)
                {
                    if(i > 0)
                    {
                        Cell& above = cells[i-1][j];
                        if(above.pond)
                        {
                            if(cell.pond && cell.pond != above.pond)
                            {
                                // edge case : join two ponds
                                fish += *above.pond;
                                for(int k=i-1; k>=0; --k)
                                {
                                    if(!cells[k][j].pond)
                                        break;
                                    cells[k][j].pond = cell.pond;
                                }
                            }
                            else
                            {
                                // point to same score tile as above cell
                                cell.pond = above.pond;
                            }
                        }
                    }

                    if(j > 0)
                    {
                        Cell& left = cells[i][j-1];
                        if(left.pond)
                        {
                            if(cell.pond && cell.pond != left.pond)
                            {
                                // edge case : join two ponds
                                fish += *left.pond;
                                for(int k=j-1; k>=0; --k)
                                {
                                    if(!cells[i][k].pond)
                                        break;
                                    cells[i][k].pond = cell.pond;
                                }
                            }
                            else
                            {
                                // point to same score tile as left cell
                                cell.pond = left.pond;
                            }
                        }
                    }

                    // start a new pond
                    if(!cell.pond)
                    {
                        std::cout << "(NEW POND) ";
                        cell.pond = &cell.score;
                    }
                    else
                    {
                        std::cout << "(OLD POND : score = " << *cell.pond << ", fish = " << fish << ") ";
                    }

                    *cell.pond = *cell.pond + fish;
                    std::cout << "[" << i << "][" << j << "] : pond is " << cell.pond << " and score is " << *cell.pond << std::endl;

                    if(*cell.pond > bestScore)
                        bestScore = *cell.pond;
                }
            }
        }

        return bestScore;
    }
};

// includes for tests
#include <random>
#include <algorithm>
#include <memory>

unique_ptr<vector<vector<int>>> create_test_matrix(size_t w, size_t h)
{
    std::random_device seed{};
    std::mt19937 rng{ seed() };
    uniform_int_distribution<int> dice{0, 10};

    auto grid = std::make_unique<vector<vector<int>>>();
    for(int i=0; i<h; ++i)
    {
        vector<int> row{};
        for(int j=0; j<w; ++j)
        {
            // default: land
            int cell = 0;

            // ~30% chance of water
            int roll = dice(rng);
            if(roll > 3)
                cell = dice(rng);

            row.push_back(cell);
        }
        grid->push_back(row); // copy
    }

    // TODO: test case [[0,1,0,5,5],[2,8,2,0,5],[8,0,2,1,9],[2,8,5,6,2],[2,1,4,0,6]]

    return grid;
}

ostream& operator<<(ostream& os, vector<vector<int>> vec)
{
    for_each(begin(vec), end(vec), [&os](const vector<int>& row) {
        for_each(begin(row), end(row), [&os](int cell) {
            os << cell << " ";
        });
        os << std::endl;
    });
    return os;
}

int main(int argc, char *argv[])
{
    unique_ptr<vector<vector<int>>> grid = create_test_matrix(4,4);
    std::cout << "Grid: " << std::endl << *grid << std::endl;

    Solution solution{};
    int maxFish = solution.findMaxFish(*grid);

    std::cout << "Max fish: " << maxFish << std::endl;
    return 0;
}