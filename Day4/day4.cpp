#include <iostream>
#include <fstream>
#include <string>

struct boundaries
{
    int left = 0;
    int right = 0;
};

int main()
{
    std::ifstream file("data.txt");
    if (!file.is_open())
    {
        std::cout << "file not found\n";
        return -1;
    }

    int count1 = 0;
    int count2 = 0;

    std::string tmp;
    boundaries f,s;
    while(file >> f.left >> tmp >> f.right >> tmp >> s.left >> tmp >> s.right)
    {
        if((f.left <= s.left && s.right <= f.right) || (s.left <= f.left && f.right <= s.right))
        {
            ++count1;
        }

        if((f.left <= s.left && s.left <= f.right) || (s.left <= f.left && f.left <= s.right))
        {
            ++count2;
        }
    }
    
    std::cout << "result 1 : " << count1
            << "\nresult 2 : " << count2 << "\n";
}
