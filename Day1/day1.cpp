#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main()
{
    std::ifstream file("data.txt");
    if(!file.is_open())
    {
        std::cout << "file not found\n";
        return -1;
    }

    std::vector<int> calories;
    std::string line = "";

    do
    {
        //dont mind attributes, i just wanted to try it >.<
        if(line == "") [[unlikely]]
        {
            calories.emplace_back(0);
        }
        else [[likely]]
        {
            calories.back() += std::stoi(line);
        }
    } 
    while(std::getline(file, line));

    std::nth_element(calories.begin(), calories.begin()+2, calories.end(), [](const int l, const int r){return l > r;});

    auto f = calories[0];
    auto s = calories[1];
    auto t = calories[2];
    
    std::cout << "max value : " << f << "\n three first : " << f + s + t << "\n";
}
