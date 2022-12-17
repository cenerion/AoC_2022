#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>


bool check(std::map<char,int>& log)
{
    for(const auto [key, val] : log)
    {
        if(val > 1)
            return false;
    }
    return true;
}

int main()
{
    std::ifstream file("data.txt");
    if (!file.is_open())
    {
        std::cout << "file not found\n";
        return -1;
    }

    std::vector<char> buffer;
    buffer.resize(4096);

    file.read(buffer.data(), 4096);

    std::map<char, int> log;

    for(int i = 0; i < 14; ++i)
    {
        log[buffer[i]] += 1;
    }

    for(int i = 13; i < buffer.size();)
    {
        log[buffer[i-13]] -= 1;
        ++i;
        log[buffer[i]] += 1;
        if(check(log))
        {
            std::cout << "result: " << i+1 << "\n";
            break;
        }
    }
    
    



}
