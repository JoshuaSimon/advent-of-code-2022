/*
    Advent of Code 2022 - Day 1, Part 2 - Joshua Simon.
    Compile and run this program with 
    clang++ day_01_2.cpp -std=c++20 && ./a.out
*/

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>
#include <vector>


int total_sum_from_list(std::vector<int> calories_list, int top_n)
{
    // Sort the vector in descending order.
    sort(calories_list.begin(), calories_list.end(), std::greater<int>());

    // Calculate the sum of the first `top_n` elements
    // in the vector.
    int total = 0;
    for (auto x : std::vector<int>(calories_list.begin(), calories_list.begin() + top_n))
        total += x;

    return total;
}


int main(void) {

    std::string filepath = "input.txt";
    if (std::filesystem::exists(filepath)) 
    {
        int max_calories = 0;
        int sum_calories = 0;
        std::vector<int> calories_list;

        std::string line;
        std::ifstream infile(filepath);
        while (std::getline(infile, line))
        {
            std::istringstream iss(line);
            int calories;
            
            // If the current line does not contain an integer
            // the string stream is interrupted.
            if (!(iss >> calories)) 
            { 
                calories_list.push_back(sum_calories);

                // Current sum is reset for a new block, also a blank
                // line is equal to 0 calories.
                calories = 0;
                sum_calories = 0;
            }

            sum_calories += calories;
        }

        max_calories = total_sum_from_list(calories_list, 3);
        std::cout << "Total max. calories: " << max_calories << std::endl;
    }

    return 0;
}