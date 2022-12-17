#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>

struct Pos
{
    int x = 0;
    int y = 0;
   
    int distance(const Pos& p) const
    {
        return std::max({std::abs(p.x - x), std::abs(p.y - y)});
    }

    Pos operator-(const Pos& r) const
    {
        return Pos(x - r.x, y - r.y);
    }

    Pos operator+(const Pos& r) const
    {
        return Pos(x + r.x, y + r.y);
    }

    bool operator==(const Pos& r) const
    {
        return x == r.x && y == r.y;
    }

    bool operator<(const Pos& r)
    {
        if(x < r.x )
            return true;
        else if(x == r.x)
            return y < r.y;
        return false;
    }

    friend
    bool operator<(const Pos& l, const Pos& r)
    {
        if(l.x < r.x )
            return true;
        else if(l.x == r.x)
            return l.y < r.y;
        return false;
    }

};

void move(Pos& p, char dir)
{
    switch(dir)
    {
        case 'U':
            ++p.y;
        break;
        case 'D':
            --p.y;
        break;
        case 'L':
            --p.x;
        break;
        case 'R':
            ++p.x;
        break;
    }
}

int sgn(int val) {
    return (0 < val) - (val < 0);
}

int main()
{
    std::ifstream file("data.txt");
    if (!file.is_open())
    {
        std::cout << "file not found\n";
        return -1;
    }

    Pos headPos;
    Pos tailPos[9];
    std::set<Pos> tailPositions1;
    std::set<Pos> tailPositions9;
    tailPositions1.insert(tailPos[0]);
    tailPositions9.insert(tailPos[8]);

    std::string direction;
    int steps = 0;
    while(file >> direction >> steps)
    {
        for(int s = steps; s > 0; --s)
        {
            move(headPos, direction[0]);
            for(int i = 0; i < 9; ++i)
            {
                Pos dif;
                if(i == 0)
                    dif = headPos - tailPos[i];
                else
                    dif = tailPos[i-1] - tailPos[i];
                    
                if(std::abs(dif.x) > 1 || std::abs(dif.y) > 1)
                {
                    tailPos[i] = tailPos[i] + Pos{sgn(dif.x), sgn(dif.y)};
                }
            }
            tailPositions1.insert(tailPos[0]);
            tailPositions9.insert(tailPos[8]);
        }
    }

    std::cout << "Part 1 : " << tailPositions1.size() << "\n";
    std::cout << "Part 2 : " << tailPositions9.size() << "\n";
}
