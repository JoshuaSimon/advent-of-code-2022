/*
    Advent of Code 2022 - Day 9, Part 1 and 2 - Joshua Simon.
    Compile and run this program with 
    clang++ day_09.cpp -std=c++20 && ./a.out
*/

#include <iostream>
#include <algorithm>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <vector>


int cast_char_to_int(char c)
{
    return int(c) - 48;
}


std::string cast_int_to_string(int i)
{
    return std::to_string(i);
}


std::vector<int> get_next_position_head(int pos_x_head, int pos_y_head, char direction)
{
    switch (direction)
    {
        case 'U': pos_y_head++; break;
        case 'D': pos_y_head--; break;
        case 'L': pos_x_head--; break;
        case 'R': pos_x_head++; break;
    }

    std::vector<int> result = { pos_x_head, pos_y_head };
    return result;
}


std::vector<int> get_next_position_tail(int pos_x_head, int pos_y_head, int pos_x_tail, int pos_y_tail, char direction)
{
    // Move if the distance is two in either direction
    if (std::abs(pos_y_head - pos_y_tail) >= 2) 
    {
        pos_y_tail += (pos_y_head - pos_y_tail) / 2;
        // If we are also on a diagonal, head.colum - tail.column
        // will be 1 or -1, resulting in a diagonal move.
        pos_x_tail += pos_x_head - pos_x_tail;
    } 
    else if (std::abs(pos_x_head - pos_x_tail) >= 2) 
    {
        // Same, but for the columns.
        pos_x_tail += (pos_x_head - pos_x_tail) / 2;
        pos_y_tail += pos_y_head - pos_y_tail;
    }

    // if (std::abs(pos_y_head - pos_y_tail) >= 2) 
    // {
    //     pos_y_tail += (pos_y_head - pos_y_tail) / 2;
    //     if (std::abs(pos_x_head - pos_x_tail) >= 2)
    //         pos_x_tail += (pos_x_head - pos_x_tail) / 2;
    //     else
    //         pos_x_tail += pos_x_head - pos_x_tail;
    // } else if (std::abs(pos_x_head - pos_x_tail) >= 2) 
    // {
    //     pos_x_tail += (pos_x_head - pos_x_tail) / 2;
    //     pos_y_tail += pos_x_tail - pos_y_tail;
    // }

    std::vector<int> result;
    result.push_back(pos_x_tail);
    result.push_back(pos_y_tail);
    return result;
}


std::string get_position_string(int x, int y)
{
    return cast_int_to_string(x) + "," + cast_int_to_string(y);
}


void insert_position(std::map<std::string, int>& pos_visits, std::string pos_str)
{
    if (pos_visits.find(pos_str) == pos_visits.end())
    {
        // Position not discovered yet.
        pos_visits.insert({pos_str, 1});
    } 
    else 
    {
        // Position already discovered.
        pos_visits[pos_str] += 1;
    }
}


int main(void)
{
    std::string filepath = "input.txt";
    std::ifstream infile(filepath);
    std::string line;

    // Map for storing the position and the number
    // of visits for the position. A position is 
    // defined by its integer x and y coordinates.
    std::map<std::string, int> pos_visits;

    // Start position.
    int pos_x_head = 0;
    int pos_y_head = 0;
    int pos_x_tail = 0;
    int pos_y_tail = 0;
    insert_position(pos_visits, get_position_string(pos_x_tail, pos_y_tail));

    while (std::getline(infile, line))
    {
        // Parse the input.
        int n_steps;
        char direction, steps;
        std::istringstream iss(line);
        iss >> direction >> steps;
        n_steps = cast_char_to_int(steps);

        // Next position.
        for (int i = 1; i <= n_steps; i++)
        {
            std::vector<int> next_pos_head(2);
            std::vector<int> next_pos_tail(2);
            next_pos_head = get_next_position_head(pos_x_head, pos_y_head, direction);

            pos_x_head = next_pos_head[0];
            pos_y_head = next_pos_head[1];

            next_pos_tail = get_next_position_tail(pos_x_head, pos_y_head, pos_x_tail, pos_y_tail, direction);
            insert_position(pos_visits, get_position_string(next_pos_tail[0], next_pos_tail[1]));
        
            pos_x_tail = next_pos_tail[0];
            pos_y_tail = next_pos_tail[1];

            std::cout << "Move: " << direction << " n = " << i << "   Pos: " << pos_x_head << " " << pos_y_head << " " << pos_x_tail << " " << pos_y_tail << std::endl;
        }
    }

    // Part 1: Position visited at least once.
    int count_part_1 = 0;
    for (auto pair : pos_visits)
    {
        std::cout << "Position = " << pair.first << "   Count = " << pair.second << std::endl;
        if(pair.second >= 1) { count_part_1++; }
    }
    std::cout << "Part 1: Position visited at least once: " << count_part_1 << std::endl;

    return 0;
}