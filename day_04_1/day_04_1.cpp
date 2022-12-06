/*
    Advent of Code 2022 - Day 4, Part 1 - Joshua Simon.
    Compile and run this program with 
    clang++ day_04_1.cpp -std=c++20 && ./a.out
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


/// Splits a string `str` at the position of `delimiter` into two parts.
/// Returns a vector containing both parts of the string without
/// the delimiter.
std::vector<std::string> split_str(std::string str, std::string delimiter)
{
    std::vector<std::string> result(2);
    size_t split_pos = str.find(delimiter);
    result[0] = str.substr(0, split_pos);
    result[1] = str.substr(split_pos + 1, str.length());
    return result;
}


std::vector<int> parse_input(std::string line)
{
    std::vector<std::string> elfs(2);
    elfs = split_str(line, ",");

    std::vector<int> bounds;
    for (auto elf : elfs)
    {
        std::vector<std::string> numbers(2);
        numbers = split_str(elf, "-");
        bounds.push_back(std::stoi(numbers[0]));
        bounds.push_back(std::stoi(numbers[1]));
    }

    return bounds;
}


int main(void)
{
    std::string filepath = "input.txt";
    std::ifstream infile(filepath);
    std::string line;

    int pairs = 0;
    while (std::getline(infile, line))
    {
        std::vector<int> bounds(4);
        bounds =  parse_input(line);

        if (bounds[0] >= bounds[2] && bounds[1] <= bounds[3])
            pairs +=1;
        else if (bounds[2] >= bounds[0] && bounds[3] <= bounds[1])
            pairs +=1;
    }

    std::cout << "Number of fully overlapping pairs: " << pairs << std::endl;
    return 0;
}
