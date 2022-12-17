#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ranges>
#include <variant>
#include <utility>

struct List
{
    std::vector<std::variant<int,List> > items;

    auto& operator[](size_t i) noexcept
    {
        return items[i];
    }

    const auto& operator[](size_t i) const noexcept
    {
        return items[i];
    }

    auto& emplace_back(int && val)
    {
        return items.emplace_back(std::move(val));
    }
    
    auto& emplace_back(List && val)
    {
        return items.emplace_back(std::move(val));
    }

    friend bool operator<(const List& l, const List& r);
};


int isRightOrder(const List& l1, const List& l2)
{
    for(int i = 0; i < l1.items.size() && i < l2.items.size(); ++i)
    {
        if(std::holds_alternative<int>(l1[i]) && std::holds_alternative<int>(l2[i]))
        {
            int l = std::get<int>(l1[i]);
            int r = std::get<int>(l2[i]);
            if(l < r)
                return 1;
            if(l > r)
                return -1;
        }
        else if(std::holds_alternative<List>(l1[i]) && std::holds_alternative<List>(l2[i]))
        {
            const List& i1 = std::get<List>(l1[i]);
            const List& i2 = std::get<List>(l2[i]);
            int ret = isRightOrder(i1, i2);
            if(ret == 1)
                return 1;
            if(ret == -1)
                return -1;
        }
        else if(std::holds_alternative<List>(l1[i]))
        {
            const List& i1 = std::get<List>(l1[i]);
            List i2;
            i2.items.emplace_back(std::get<int>(l2[i]));
            int ret = isRightOrder(i1, i2);
            if(ret == 1)
                return 1;
            if(ret == -1)
                return -1;
        }
        else if(std::holds_alternative<List>(l2[i]))
        {
            List i1;
            const List& i2 = std::get<List>(l2[i]);
            i1.items.emplace_back(std::get<int>(l1[i]));
            int ret = isRightOrder(i1, i2);
            if(ret == 1)
                return 1;
            if(ret == -1)
                return -1;
        }
    }

    if(l1.items.size() < l2.items.size())
        return 1;
    if(l1.items.size() > l2.items.size())
        return -1;

    return 0;
}


bool operator<(const List& l, const List& r)
{
    if(isRightOrder(l,r) == 1)
        return true;
    return false;
}


List parse(const std::string& s, int& off)
{
    List tmp;

    for(++off; off < s.size(); ++off)
    {
        if(s[off] == '[')
        {
            tmp.emplace_back(parse(s, off));
            continue;
        }
        else if(s[off] == ']')
        {
            return tmp;
        }
        else if(s[off] >= '0' && s[off] <= '9')
        {
            size_t count = 0;
            tmp.emplace_back(std::stoi(s.substr(off), &count));
            off += static_cast<int>(count)-1;
        }
    }

    std::cerr << "ERROR: unexpected EOF\n";
    std::abort();
}

List parse(const std::string& s)
{
    int tmp = 0;
    return parse(s, tmp);
}

std::string to_string(const List& l)
{
    std::string result = "[";
    bool once = true;

    for(const auto& it : l.items)
    {
        
        if(once) [[unlikely]]
        {
            once = false;
        }
        else [[likely]]
            result += ",";

        if(std::holds_alternative<int>(it))
            result += std::to_string(std::get<int>(it));
        else if(std::holds_alternative<List>(it))
            result += to_string(std::get<List>(it));

    }
    result += "]";
    return result;
}



int main()
{
    std::ifstream file("data.txt");
    if (!file.is_open())
    {
        std::cout << "file not found\n";
        return -1;
    }

    std::vector<List> packets;

    std::string line1;
    std::string line2;
    std::string tmp;
    int counter = 0;
    int index = 1;
    while(std::getline(file, line1) && std::getline(file, line2))
    {
        auto list1 = parse(line1);
        auto list2 = parse(line2);
        packets.emplace_back(list1);
        packets.emplace_back(list2);

        if(list1 < list2)
            counter += index;
        
        ++index;
        std::getline(file,tmp);
    }
    
    std::cout << "result 1 : " << counter << "\n";

    //insert [[2]] & [[6]]
    packets.emplace_back(parse("[[2]]"));
    packets.emplace_back(parse("[[6]]"));
    
    std::ranges::sort(packets, [](const List& l, const List&r){return l < r;});

    //display & find manualy, or TODO: find this two lists, get their indexes and multiply
    index = 1;
    for(const auto& it:packets)
    {
        std::cout << index << " : " << to_string(it) << "\n";
        ++index;
    }
}