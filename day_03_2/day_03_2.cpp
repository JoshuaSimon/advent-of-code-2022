/*
    Advent of Code 2022 - Day 3, Part 2 - Joshua Simon.
    Compile and run this program with 
    clang++ day_03_2.cpp -std=c++20 && ./a.out
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


std::string find_duplicates(std::string string_1, std::string string_2)
{
    std::string result;
    for (auto c : string_1)
    {
        if (string_2.find(c) != std::string::npos)
        {   
            result += c;
        }
    }
    return result;
}


int get_priority(char c)
{
    int ascii_number = int(c);

    // Letters 'a' to 'z'.
    if (ascii_number >= 97 && ascii_number <= 122)
    {
        return ascii_number - 96;
    } 
    else
    {
        return ascii_number - 38;
    }
}


int main(void)
{
    std::string filepath = "input.txt";
    std::ifstream infile(filepath);
    std::string line;

    int counter = 0;
    int total_priority = 0;
    std::vector<std::string> rucksacks(3);
    while (std::getline(infile, line))
    {
        rucksacks[counter] = line;

        if (counter == 2)
        {
            std::string rucksacks_12 = find_duplicates(rucksacks[0], rucksacks[1]);
            std::string badge_123 = find_duplicates(rucksacks_12, rucksacks[2]);
            total_priority += get_priority(badge_123[0]);
            counter = 0;
        } 
        else 
        {
            counter += 1;
        }
    }

    std::cout << "Total sum of priority is: " << total_priority << std::endl;
    return 0;
}