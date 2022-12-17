#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <ranges>
#include <algorithm>


int check(int cycle, int reg, std::vector<char>& display)
{
    auto pos = (cycle-1);
    auto posV = (pos%40);
    if(reg == posV)
    {
        display[pos] = '#';
    }
    else if(reg-1 == posV && reg-1 >= 0)
    {
        display[pos] = '#';
    }
    else if(reg+1 == posV && reg+1 <= 239)
    {
        display[pos] = '#';
    }


    switch(cycle)
    {
        case 20:
        case 60:
        case 100:
        case 140:
        case 180:
        case 220:
            std::cout << "during " << cycle << " cycle, strength is " << cycle * reg << "\n";
            return cycle * reg;

        default:
            return 0;
    }
}

int main()
{
    std::ifstream file("data.txt");
    if (!file.is_open())
    {
        std::cout << "file not found\n";
        return -1;
    }

    std::vector<char> display(6*40, '.');

    size_t sum = 0;
    int regX = 1;
    std::string opcode;

    for(int cycle = 1; cycle <= 240; ++cycle)
    {
        file >> opcode;
        
        sum += check(cycle, regX, display);
        if(opcode == "addx")
        {
            int val = 0;
            file >> val;

            ++cycle;

            sum += check(cycle, regX, display);
            regX += val;
        }
    }

    std::cout << "Part 1 : " << sum << "\n";

    for(int i = 0; auto it : display)
    {
        if(i % 40 == 0)
            std::cout << "\n";
        std::cout << it;
        ++i;
    }
    std::cout << "\n";
}
