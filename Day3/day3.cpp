#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ranges>

int letter_to_priority(char l)
{
    if(l > 96)
        return l - 96;
    return l - 38;
}

int main()
{
    std::ifstream file("data.txt");
    if (!file.is_open())
    {
        std::cout << "file not found\n";
        return -1;
    }

    int prioritySum1 = 0;
    int prioritySum2 = 0;

    std::string l1;
    std::string l2;
    std::string l3;
    while (std::getline(file, l1))
    {
        std::getline(file, l2);
        std::getline(file, l3);

        for(const auto& line : {l1, l2, l3})
        {
            auto sizeOfCompartment  = line.size() / 2;
            auto left = line.substr(0, sizeOfCompartment);
            auto right = line.substr(sizeOfCompartment);
            
            std::ranges::sort(left);
            std::ranges::sort(right);
            std::string result;

            std::ranges::set_intersection(left, right, std::back_inserter(result));
            prioritySum1 += letter_to_priority(result.front());
        }


        std::ranges::sort(l1);
        std::ranges::sort(l2);
        std::ranges::sort(l3);
        std::string out, tmp;

        std::ranges::set_intersection(l1, l2, std::back_inserter(tmp));
        std::ranges::set_intersection(tmp, l3, std::back_inserter(out));
        prioritySum2 += letter_to_priority(out.front());
    }

    std::cout << "sum1 : " << prioritySum1 << "\nsum2 : " << prioritySum2 << "\n";
}