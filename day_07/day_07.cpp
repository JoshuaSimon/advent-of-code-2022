/*
    Advent of Code 2022 - Day 7, Part 1 and 2 - Joshua Simon.
    Compile and run this program with 
    clang++ day_07.cpp -std=c++20 && ./a.out
*/

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <vector>


std::string get_path(std::vector<std::string> path)
{
    std::string output;
    for (auto name : path)
    {
        name = (name == "/") ? name : name + "/";
        output += name;
    }
    return output;
}


void cd(std::vector<std::string>& current_path, std::string arg) 
{
    if (arg == "..")
    {
        std::string parent = current_path.back();
        current_path.pop_back();
    }
    else if (arg == "/")
    {
        current_path = { "/" };
    }
    else 
    {
        current_path.push_back(arg);
    }
}


int main(void)
{
    std::string filepath = "input.txt";
    std::ifstream infile(filepath);
    std::string line;

    std::map<std::string, int> dirs;
    std::vector<std::string> current_absoulte_path;
    std::vector<std::string> parent_absoulte_path;

    while (std::getline(infile, line))
    {
        if (line[0] == '$')
        {
            // Commands
            std::istringstream iss(line);
            std::string arg, command, initalizer;
            iss >> initalizer >> command >> arg;

            if (command == "cd")
            {
                cd(current_absoulte_path, arg);
            }
        }
        else
        {
            // Files.
            std::istringstream iss(line);
            std::string filename;
            int size;
            iss >> size >> filename;

            parent_absoulte_path = current_absoulte_path;
            for (int i = current_absoulte_path.size() - 1; i >= 0; i--)
            {
                if (dirs.find(get_path(parent_absoulte_path)) == dirs.end()) 
                {
                    // Dir not discovered yet.
                    dirs.insert({get_path(parent_absoulte_path), size});
                } 
                else 
                {
                    // Dir already discovered.
                    dirs[get_path(parent_absoulte_path)] += size;
                }

                parent_absoulte_path.pop_back();
            }
        }
    }

    // Part 1.
    int max_size = 0;
    for (auto pair : dirs)
        if (pair.second <= 100000) { max_size += pair.second; }

    std::cout << "Sum of dirs for part 1: " << max_size << std::endl;

    // Part 2.
    int space_total = 70000000;
    int space_needed = 30000000 - (space_total - dirs["/"]);
    int min_size = space_total;

    for (auto pair : dirs)
    {
        if (pair.second >= space_needed && pair.second <= min_size)
        {
            min_size = pair.second;
        }
    }

    std::cout << "Space of dir for part 2: " << min_size << std::endl;
    return 0;
}