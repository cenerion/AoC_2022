#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

struct Pos
{
    int x;
    int y;
};

struct Line
{
    Pos start;
    Pos end;

};

int main()
{
    std::cout << "Day14\n";
    std::ifstream file("data.txt");
    if (!file.is_open())
    {
        std::cout << "file not found\n";
        return -1;
    }

    int lowestRock = 0;

    std::vector<Line> lines;
    std::string line;
    while(std::getline(file, line))
    {
        Pos s{0,0};
        Pos e{0,0};
        for(size_t i = 0; i < line.size();)
        {
            size_t taken = 0;
            if(i == 0) [[unlikely]]
            {
                s.x = std::stoi(line.substr(i), &taken);
                i += taken + 1;
                s.y = std::stoi(line.substr(i), &taken);
                i += taken + 4;
                if(s.y > lowestRock)
                    lowestRock = s.y;
            }
            
            e.x = std::stoi(line.substr(i), &taken);
            i += taken + 1;
            e.y = std::stoi(line.substr(i), &taken);
            i += taken + 4;
            if(e.y > lowestRock)
                lowestRock = e.y;

            lines.emplace_back(Line{s,e});
            s = e;
        }
    }

    constexpr const Pos deploymentPoint{500, 0};

    constexpr int w = 1000;
    const int h = 2 + lowestRock;

    std::vector<char> map(w*h, '.');
    for(const auto& it : lines)
    {
        if(it.start.x == it.end.x)
        {
            auto [s,e] = std::minmax(it.start.y, it.end.y);
            for(int i = s; i <= e; ++i)
            {
                map[(i * w) + it.end.x] = '#';
            }
        }
        else
        {
            auto [s,e] = std::minmax(it.start.x, it.end.x);
            for(int i = s; i <= e; ++i)
            {
                map[(it.end.y * w) + i] = '#';
            }
        }
    }

    Pos sand = deploymentPoint;
    int result1 = 0;
    int result2 = 0;
    for(;(map[500] != 'o');)
    {
        int rowBelow = ((sand.y+1) * w);
        if(sand.y == h-1)
        {
            if(result1 == 0)[[unlikely]]
                result1 = result2;

            map[(sand.y * w) + sand.x] = 'o';
            ++result2;
            sand = deploymentPoint;
            continue;
        }
        
        if(map[rowBelow + sand.x] == '.')
        {
            sand.y += 1;
        }
        else if(sand.x > 0 && map[rowBelow + sand.x -1] == '.')
        {
            sand.y += 1;
            sand.x += -1;
        }
        else if(sand.x < w-1 && map[rowBelow + sand.x+1] == '.')
        {
            sand.y += 1;
            sand.x += 1;
        }
        else
        {
            map[(sand.y * w) + sand.x] = 'o';
            ++result2;
            sand = deploymentPoint;
        }
    }

    std::cout << "result 1 : " << result1 
            << "\nresult 2 : " << result2 << "\n";
}