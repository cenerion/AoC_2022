#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <array>
#include <vector>

int main()
{
    std::ifstream file("data.txt");
    if (!file.is_open())
    {
        std::cout << "file not found\n";
        return -1;
    }

    std::vector<std::deque<char> > crates(9);

    std::string line = "";
    while (std::getline(file, line))
    {
        if(line == "")
            break;
        
        for(size_t i = 0; i < 35 ;)
        {
            auto pos = line.find('[', i);
            if(pos == std::string::npos)
                break;
        
            crates[pos/4].push_back(line[pos+1]);
            i = pos + 3;
        }
    }

    for(int i = 0; i < 9; ++i)
    {
        for(const auto& it : crates[i])
        {
            std::cout << "[" << it << "] ";
        }
        std::cout << "\n";
    }

    auto crates2 = crates;

    std::string tmp;
    int count;
    int from;
    int to;
    while (file >> tmp >> count >> tmp >> from >> tmp >> to)
    {
        //part1
        for(int i = 0; i < count; ++i)
        {
            char tmp = crates[from-1].front();
            crates[from-1].pop_front();
            crates[to-1].push_front(tmp);
        }

        //part2
        std::deque<char> temp;
        for(int i = 0; i < count; ++i)
        {
            temp.push_back(crates2[from-1].front());
            crates2[from-1].pop_front();
        }
        for(int i = 0; i < count; ++i)
        {
            crates2[to-1].push_front(temp.back());
            temp.pop_back();
        }
    }

    for(int i = 0; i < 9; ++i)
        std::cout << crates[i].front();
    std::cout << "\n";

    for(int i = 0; i < 9; ++i)
        std::cout << crates2[i].front();
    std::cout << "\n";
}
