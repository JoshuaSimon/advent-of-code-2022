/*
    Advent of Code 2022 - Day 6, Part 1 and 2 - Joshua Simon.
    Compile and run this program with 
    clang++ day_06.cpp -std=c++20 && ./a.out
*/

#include <iostream>
#include <fstream>
#include <map>
#include <string>


bool check_duplicates(std::string str)
{
    std::map<char, int> letter_counts;
    for (int i = 0; i < str.length(); i++)
        letter_counts[str[i]]++;

    for (auto letter : letter_counts)
    {
        if (letter.second > 1)
            return true;
    }

    return false;
}


int main(void)
{
    std::string filepath = "input.txt";
    std::ifstream infile(filepath);
    std::string line, window;
    std::getline(infile, line);

    int window_size_part_1 = 4;
    int window_size_part_2 = 14;

    int offset_part_1 = 1;
    int offset_part_2 = 11;

    for (auto i = 3; i < line.size(); i++)
    {
        window = line.substr(i-3, window_size_part_2);
        if (!check_duplicates(window)) 
        {
            std::cout << "First marker on i = " << i + offset_part_2 << " with value: " << window << std::endl;
            break;
        }
    }

    return 0;
}