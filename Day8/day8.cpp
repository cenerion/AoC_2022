#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::pair<bool, int> is_visible(int x, int y, const std::vector<std::vector<int> >& forest)
{
    if(x > 98 || x < 0 || y > 98 || y < 0)
        return std::make_pair(false, 0);

    auto val = forest[x][y];

    bool t = true;
    bool b = true;
    bool l = true;
    bool r = true;
    
    int top = 0;
    int bot = 0;
    int left = 0;
    int right = 0;
    
    for(int i = x+1; i < 99; ++i)
    {
        ++bot;
        if(val <= forest[i][y]){
            b = false;
            break;
        }
    }

    for(int i = x-1; i >= 0; --i)
    {
        ++top;
        if(val <= forest[i][y]){
            t = false;
            break;
        }
    }

    for(int i = y+1; i < 99; ++i)
    {
        ++right;
        if(val <= forest[x][i]){
            r = false;
            break;
        }
    }

    for(int i = y-1; i >= 0; --i)
    {
        ++left;
        if(val <= forest[x][i]){
            l = false;
            break;
        }
    }
    
    return std::make_pair(t || b || l || r, top * bot * left * right);
}

int main()
{
    std::ifstream file("data.txt");
    if (!file.is_open())
    {
        std::cout << "file not found\n";
        return -1;
    }

    std::vector<std::vector<int> > forest;
    forest.resize(99);
    for(auto& it : forest)
        it.resize(99);

    std::string line;
    for(int i = 0; i < 99; ++i)
    {
        std::getline(file, line);
        for(int j = 0; j < 99; ++j)
        {
            forest[i][j] = line[j];
        }
    }

    int visibleTrees = 0;
    int bestScore = 0;

    for(int x = 0; x < 99; ++x)
    {
        for(int y = 0; y < 99; ++y)
        {
            auto [visible, score] = is_visible(x,y,forest);
            
            if(visible)
                visibleTrees += 1;

            if(score > bestScore)
            {
                bestScore = score;
                bestX = x;
                bestY = y;
            }
        }
    }

    std::cout << "result 1 : " << visibleTrees << "\n";
    std::cout << "result 2 : " << bestScore << "\n";
}

