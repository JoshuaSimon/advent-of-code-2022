/*
    Advent of Code 2022 - Day 5, Part 1 and 2 - Joshua Simon.
    Compile and run this program with 
    clang++ day_05.cpp -std=c++20 && ./a.out
*/

#include <iostream>
#include <algorithm>
#include <fstream>
#include <ranges>
#include <string>
#include <sstream>
#include <vector>


struct CrateMove
{
    int number_of_crates;
    int from_stack;
    int to_stack;
};


CrateMove parse_moves(std::string line)
{
    std::string token_1, token_2, token_3;
    std::string identifier_1, identifier_2, identifier_3;
    std::istringstream iss(line);
    iss >> identifier_1 >> token_1 >> identifier_2 >> token_2 >> identifier_3 >> token_3;

    CrateMove result;
    result.number_of_crates = std::stoi(token_1);
    result.from_stack = std::stoi(token_2);
    result.to_stack = std::stoi(token_3);
    return result;
}


void parse_stacks(std::string line, std::vector<std::vector<char>>& stacks)
{
    for (auto i = 0; i <= line.length(); i++)
    {
        // Calculate the stack id and assign the crate 
        // to the right stack.
        if (!std::isupper(line[i])) continue;
        size_t stack_id = (i - 1) / 4;

        if (stacks.size() <= stack_id) stacks.resize(stack_id + 1);
        stacks[stack_id].push_back(line[i]);
    }
}


void move_crate_9000(std::vector<std::vector<char>>& stacks, CrateMove move)
{
    for (auto i = 0; i < move.number_of_crates; i++)
    {
        stacks[move.to_stack - 1].push_back(stacks[move.from_stack - 1].back());
        stacks[move.from_stack - 1].pop_back();
    }
}


void move_crate_9001(std::vector<std::vector<char>>& stacks, CrateMove move)
{
    std::vector<char> crates;
    for (auto i = 0; i < move.number_of_crates; i++)
    {
        crates.push_back(stacks[move.from_stack - 1].back());
        stacks[move.from_stack - 1].pop_back();
    }

    for (auto it = crates.rbegin(); it != crates.rend(); ++it)
        stacks[move.to_stack - 1].push_back(*it);
}


int main(void)
{
    std::string filepath = "input.txt";
    std::ifstream infile(filepath);
    std::string line;

    std::vector<CrateMove> crate_moves;
    std::vector<std::vector<char>> crate_stacks;

    int input_type = 0;
    while (std::getline(infile, line))
    {
       if (line.length() == 0) { input_type = 1; continue; }
       
       switch (input_type)
       {
            case 0:
                parse_stacks(line, crate_stacks);
                break;

            case 1:
                crate_moves.push_back(parse_moves(line));
                break;
        
            default:
                break;
       }
    }

    // Flip the stacks vector for a easier use with
    // `pop_back()` and `push_back()`.
    for (auto i = 0; i < crate_stacks.size(); i++)
        std::reverse(crate_stacks[i].begin(), crate_stacks[i].end());

    for (auto crate_move : crate_moves)
        move_crate_9001(crate_stacks, crate_move);

    std::cout << std::endl << "Top crates on each stack: ";
    for (auto crate_stack : crate_stacks)
        std::cout << crate_stack.back();
    std::cout << std::endl;
    return 0;
}
