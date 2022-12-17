#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

#include <chrono>

struct Pos
{
    int x = 0;
    int y = 0;
};

struct Sensor
{
    int centerX;
    int centerY;
    int radius;
    int beaconX;
    int beaconY;

    bool isPosInRadius(int x, int y) const
    {
        return radius >= (std::abs(centerX - x) + std::abs(centerY - y));
    }

    int radiusInParticularRow(int y) const
    {
        int r = radius - std::abs(y - centerY);
        if(r >= 0)
        {
            return r;
        }
        return 0;
    }
};

int main()
{
    std::cout << "Day15\n";
    std::ifstream file("data.txt");
    if (!file.is_open())
    {
        std::cout << "file not found\n";
        return -1;
    }

    std::vector<Sensor> sensors;
    std::vector<Pos> discoveredBeacons;

    std::string tmp;
    std::string x1,y1, x2,y2;
    //Sensor at x=2483411, y=3902983: closest beacon is at x=2289579, y=3633785
    while(file >> tmp >> tmp >> x1 >> y1 >> tmp >> tmp >> tmp >> tmp >> x2 >> y2)
    {
        Sensor sensor;
        Pos beacon;
        sensor.centerX = std::stoi(x1.substr(2));
        sensor.centerY = std::stoi(y1.substr(2));
        beacon.x = std::stoi(x2.substr(2));
        beacon.y = std::stoi(y2.substr(2));

        sensor.radius = std::abs(sensor.centerX - beacon.x) + std::abs(sensor.centerY - beacon.y);

        sensors.emplace_back(sensor);
    }

    
    std::cout << "Part 1\n";

    constexpr const int yTocheck = 2000000;
    //constexpr const int rowTocheck = 10;

    std::set<int> checkedColumns;
    for(const auto& it : sensors)
    {
        for(int i = it.radiusInParticularRow(yTocheck); i >= 0; --i)
        {
            checkedColumns.insert(it.centerX + i);
            checkedColumns.insert(it.centerX - i);
        }
    }

    for(const auto& it : discoveredBeacons)
    {
        if(it.y == yTocheck)
            checkedColumns.erase(it.x);
    }

    std::cout << "result 1 : " << checkedColumns.size() << "\n";
    

    std::cout << "Part 2\n";

    int posX = 0, posY = 0;
    for(int y = 0; y <= 4000000; ++y)
    {
        for(int x = 0; x <= 4000000; ++x)
        {
            bool notInRange = true;
            for(const auto& it : sensors)
            {
                if(it.isPosInRadius(x,y))
                {
                    notInRange = false;
                    x = it.centerX + it.radiusInParticularRow(y);
                    break;
                }
            }
            if(notInRange)[[unlikely]]
            {
                posX = x;
                posY = y;
                
                x = 4000001;
                y = 4000001;
                break;
            }
        }
    }

    std::cout << "result 2 : " << (static_cast<unsigned long long>(posX) * 4000000) + posY << "\n";
}
