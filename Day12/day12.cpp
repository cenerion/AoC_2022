#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <ranges>

struct Node
{
    int id;
    char height;
    std::vector<int> neighbours;
};

std::vector<int> dijsktra(const std::vector<Node>& nodelist, int start)
{
    //TODO : change Q&S maps to vector<bool> QS
    std::map<int, Node> Q;
    std::map<int, Node> S;
    for(auto& it : nodelist)
    {
        Q[it.id] = it;
    }

    auto size = nodelist.size();
    std::vector<int> p(size, -1);
    std::vector<int> d(size, std::numeric_limits<int>::max()-10);

    d[start] = 0;

    while(!Q.empty())
    {
        auto iter = std::ranges::min_element(Q,
            [&d](const auto& l, const auto& r)
            {
                auto& [lk, lv] = l;
                auto& [rk, rv] = r;
                return d[lk] < d[rk];
            });

        if(iter == Q.end())
        {
            std::cout << "Error\n";
            std::abort();
        }

        auto minIdx = iter->first;
        
        S[minIdx] = Q[minIdx];
        Q.erase(minIdx);

        for(auto& it: S[minIdx].neighbours)
        {
            auto tmp = d[minIdx] + 1;
            if(d[it] > tmp)
            {
                d[it] = d[minIdx] + 1;
                p[it] = minIdx;
            }
        }
    }

    return d;
}

int main()
{
    std::ifstream file("data.txt");
    if (!file.is_open())
    {
        std::cout << "file not found\n";
        return -1;
    }

    std::vector<std::string> map;
    std::string line;
    while(std::getline(file, line))
    {
        map.emplace_back(line);
    }
    file.close();

    int h = static_cast<int>(map.size());
    int w = static_cast<int>(map[0].size());

    std::vector<Node> nodes(h * w);
    
    int startIdx = 0;
    int endIdx = 0;

    for(int y = 0; y < h; ++y)
    {
        for(int x = 0; x < w; ++x)
        {
            int position = (y*w) + x;
            nodes[position].id = position;

            auto point = map[y][x];
            nodes[position].height = point;

            if(point == 'S')
            {
                startIdx = position;
                point = 'a';
            }
            else if(point == 'E')
            {
                endIdx = position;
                point = 'z';
            }

            if(y > 0)
            {
                auto up = map[y-1][x];
                if( (up - point) <= 1)
                    nodes[position - w].neighbours.push_back(position);
            }
            if(y < map.size()-1)
            {
                auto down = map[y+1][x];
                if( (down - point) <= 1)
                    nodes[position + w].neighbours.push_back(position);
            }
            if(x > 0)
            {
                auto left = map[y][x-1];
                if( (left - point) <= 1)
                    nodes[position - 1].neighbours.push_back(position);
            }
            if(x < map[y].size()-1)
            {
                auto right = map[y][x+1];
                if( (right - point) <= 1)
                    nodes[position+1].neighbours.push_back(position);
            }
        }
    }

    auto ret = dijsktra(nodes, endIdx);

    std::cout << "result 1 : " << ret[startIdx] << "\n";

    int min = 2147483637;
    for(int i = 0; i < w*h; ++i)
    {
        if(nodes[i].height == 'a')
        {
            auto tmp = ret[i];
            if(tmp < min)
                min = tmp;
        }
    }

    std::cout << "result 1 : " << min << "\n";
}