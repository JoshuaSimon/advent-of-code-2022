/*
    Advent of Code 2022 - Day 3, Part 1 - Joshua Simon.
    Compile and run this program with 
    clang++ day_03_1.cpp -std=c++20 && ./a.out
*/

#include <iostream>
#include <fstream>
#include <string>


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

    int total_priority = 0;
    while (std::getline(infile, line))
    {
        std::string compartment_1 = line.substr(0, line.length() / 2);
        std::string compartment_2 = line.substr(line.length() / 2, line.length());

        int priority;
        for (auto c : compartment_1)
        {
            if (compartment_2.find(c) != std::string::npos)
            {
                priority = get_priority(c);
                break;
            }
        }
        total_priority += priority;
    }

    std::cout << "Total sum of priority is: " << total_priority << std::endl;
    return 0;
}