/*
    Advent of Code 2022 - Day 2, Part 1 - Joshua Simon.
    Compile and run this program with 
    clang++ day_02_1.cpp -std=c++20 && ./a.out
*/

#include <iostream>
#include <fstream>
#include <map>
#include <string>


// Maps moves from player 2 to player 1's moves.
std::map<char, char> moves_map = 
{
    { 'X', 'A' },
    { 'Y', 'B' },
    { 'Z', 'C' }
};

// Map containing points for the game moves.
std::map<char, int> points_map = 
{
    { 'A', 1 },
    { 'B', 2 },
    { 'C', 3 },
    { 'X', 1 },
    { 'Y', 2 },
    { 'Z', 3 }
};


int parse_game(char move_p1, char move_p2)
{
    if (move_p1 == moves_map.at(move_p2))
    {
        return 3;
    }
    else if (move_p1 == 'C' && move_p2 == 'X')
    {
        return 6;
    }
    else if (move_p1 == 'A' && move_p2 == 'Y')
    {
        return 6;
    }
    else if (move_p1 == 'B' && move_p2 == 'Z')
    {
        return 6;
    }
    else 
    {
        return 0;
    }
}


int main(void)
{
    std::string filepath = "input.txt";
    std::ifstream infile(filepath);

    int total_points = 0;
    char move_p1, move_p2;
    while (infile >> move_p1 >> move_p2)
    {
        total_points += parse_game(move_p1, move_p2) + points_map.at(move_p2);
    }

    std::cout << "Total points are: " << total_points << std::endl;
    return 0;
}