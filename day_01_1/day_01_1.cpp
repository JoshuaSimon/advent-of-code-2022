/*
    Advent of Code 2022 - Day 1, Part 1 - Joshua Simon.
    Compile and run this program with 
    clang++ day_01_1.cpp -std=c++20 && ./a.out
*/

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>

int main(void) 
{
    std::string filepath = "input.txt";
    if (std::filesystem::exists(filepath)) 
    {
        int max_calories = 0;
        int sum_calories = 0;

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
                // Check if the current sum of calories is a
                // new maxima.
                if (sum_calories >= max_calories)
                {
                    max_calories = sum_calories;
                }

                // Current sum is reset for a new block, also a blank
                // line is equal to 0 calories.
                calories = 0;
                sum_calories = 0;
            }

            sum_calories += calories;
            std::cout << calories << " " << sum_calories << std::endl;
        }

        std::cout << "Total max. calories: " << max_calories << std::endl;
    }

    return 0;
}