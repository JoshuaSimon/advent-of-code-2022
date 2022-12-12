/*
    Advent of Code 2022 - Day 8, Part 1 and 2 - Joshua Simon.
    Compile and run this program with 
    clang++ day_08.cpp -std=c++20 && ./a.out
*/

#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>


bool is_visible(std::vector<std::vector<int>> tree_matrix, size_t row_idx, size_t col_idx)
{
    // Row left max.
    auto it = std::max_element(std::begin(tree_matrix[row_idx]), std::begin(tree_matrix[row_idx]) + col_idx);
    int row_max_left = *it;

    // Row right max.
    it = std::max_element(std::begin(tree_matrix[row_idx]) + col_idx + 1, std::end(tree_matrix[row_idx]));
    int row_max_right = *it;

    // Column left max.
    int col_max_left = 0;
    for (int i = 0; i < row_idx; i++)
    {
        col_max_left = (tree_matrix[i][col_idx] > col_max_left) ? tree_matrix[i][col_idx] : col_max_left;
    }

    // Column right max.
    int col_max_right = 0;
    for (int i = row_idx + 1; i < tree_matrix[row_idx].size(); i++)
    {
        col_max_right = (tree_matrix[i][col_idx] > col_max_right) ? tree_matrix[i][col_idx] : col_max_right;
    }

    int tree = tree_matrix[row_idx][col_idx];
    if (tree > row_max_left || tree > row_max_right || tree > col_max_left || tree > col_max_right)
    {
        return true;
    }
    else
    {
        return false;
    }
}


int scenic_score(std::vector<std::vector<int>> tree_matrix, size_t row_idx, size_t col_idx)
{
    int tree = tree_matrix[row_idx][col_idx];
    auto row = tree_matrix[row_idx];

    int score_up, score_down, score_left, score_right;
    score_up = score_down = score_left = score_right = 0;

    // Row left.
    for (int i = col_idx - 1; i >= 0; i--)
    {
        if (row[i] < tree) 
        {
            score_left += 1;
        }
        else if (row[i] == tree)
        {
            score_left += 1;
            break;
        }
        else
        {
            score_left += 1;
            break;
        }
    }

    // Row right.
    for (int i = col_idx + 1; i < row.size(); i++)
    {
        if (row[i] < tree) 
        {
            score_right += 1;
        }
        else if (row[i] == tree)
        {
            score_right += 1;
            break;
        }
        else
        {
            score_right += 1;
            break;
        }
    }

     // Column up.
    for (int i = row_idx - 1; i >= 0; i--)
    {
        if (tree_matrix[i][col_idx] < tree)
        {
            score_up += 1;
        }
        else if (tree_matrix[i][col_idx]  == tree)
        {
            score_up += 1;
            break;
        }
        else
        {
            score_up += 1;
            break;
        }
    }

    // Column down.
    for (int i = row_idx + 1; i < tree_matrix.size(); i++)
    {
        if (tree_matrix[i][col_idx] < tree)
        {
            score_down += 1;
        }
        else if (tree_matrix[i][col_idx]  == tree)
        {
            score_down += 1;
            break;
        }
        else
        {
            score_down += 1;
            break;
        }
    }

    return score_up * score_down * score_left * score_right;
}


int main(void)
{
    std::string filepath = "input.txt";
    std::ifstream infile(filepath);
    std::string line;

    std::vector<std::vector<int>> tree_matrix;
    while (std::getline(infile, line))
    {
        std::vector<int> tree_col;
        for (auto c : line)
        {
            tree_col.push_back(int(c) - 48);
        }
        tree_matrix.push_back(tree_col);
    }

    int visible_trees = 0;
    int highest_score = 0;
    for (int row_idx = 1; row_idx < tree_matrix.size() - 1; row_idx++)
    {
        for (int col_idx = 1; col_idx < tree_matrix[0].size() - 1; col_idx++)
        {
            if (is_visible(tree_matrix, row_idx, col_idx))
            {
                visible_trees += 1;
            }

            int score = scenic_score(tree_matrix, row_idx, col_idx);
            if (score > highest_score)
            {
                highest_score = score;
            }
        }
    }

    // Part 1.
    visible_trees += tree_matrix.size() * 2 + 2 * (tree_matrix[0].size() - 2);
    std::cout << "Number of visible trees: " << visible_trees << std::endl;

    // Part 2.
    std::cout << "Highest score: " << highest_score << std::endl;

    return 0;
}