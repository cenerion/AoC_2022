#include <fstream>
#include <iostream>
#include <string>

int parse_oponent_input(char a)
{
    switch (a)
    {
    case 'A':
        return 1;
    case 'B':
        return 2;
    case 'C':
        return 3;
    default:
        return 0;
    }
}

int parse_my_input(char a)
{
    switch (a)
    {
    case 'X':
        return 1;
    case 'Y':
        return 2;
    case 'Z':
        return 3;
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

    std::string line = "";
    int myScore1 = 0;
    int myScore2 = 0;

    while (std::getline(file, line))
    {
        int opponentMove = parse_oponent_input(line[0]);
        int myMove = parse_my_input(line[2]);

        if(!opponentMove || !myMove)
        {
            std::cout << "Error: invalid input: \"" << line << "\"\n";
            return 1;
        }

        switch (opponentMove - myMove)
        {
        case 0:
            myScore1 += myMove + 3;
            break;

        case 2:
        case -1:
            myScore1 += myMove + 6;
            break;

        case 1:
        case -2:
            myScore1 += myMove;
            break;
        }

        switch (myMove)
        {
        case 1:
        {
            int tmp = opponentMove - 1;
            if (tmp == 0)
                tmp = 3;
            myScore2 += tmp;
        }
        break;

        case 2:
            myScore2 += opponentMove + 3;
        break;

        case 3:
        {
            int tmp = opponentMove + 1;
            if (tmp == 4)
                tmp = 1;
            myScore2 += tmp + 6;
        }
        break;
        }
    }

    std::cout << "score for 1st star: " << myScore1 
            << "\n score for 2nd star: " << myScore2 << "\n";
}