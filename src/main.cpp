#include "Club.h"

#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Missing input file\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file)
    {
        std::cerr << "Can't open input file\n";
        return 1;
    }

    std::string line;
    int lineNo = 1;
    int tableCount;
    ClubTime openTime, closeTime;
    int price;

    if (!std::getline(file, line))
        return 0;
    try
    {
        tableCount = std::stoi(line);
        if (tableCount <= 0)
            throw std::runtime_error("incorrect count of tables");
    }
    catch (...)
    {
        std::cout << line << "\n";
        return 0;
    }
    ++lineNo;

    if (!std::getline(file, line))
        return 0;

    std::istringstream iss(line);
    std::string openStr, closeStr;

    if (!(iss >> openStr >> closeStr) || !(iss >> std::ws).eof())
    {
        std::cout << line << std::endl;
        return 0;
    }
    try
    {
        openTime = ClubTime::parse(openStr);
        closeTime = ClubTime::parse(closeStr);
    }
    catch (...)
    {
        std::cout << line << std::endl;
        return 0;
    }

    ++lineNo;

    if (!std::getline(file, line))
        return 0;
    try
    {
        price = std::stoi(line);
        if (price <= 0) throw std::runtime_error("incorrect price");
    }
    catch (...)
    {
        std::cout << line << std::endl;
        return 0;
    }
    ++lineNo;

    Club club(tableCount, openTime, closeTime, price);

    while (std::getline(file, line))
    {
        if (line.empty())
        {
            ++lineNo;
            continue;
        }

        Event e;
        try {
            e = Event::fromString(line);
        }
        catch (...) {
            std::cout << line << std::endl;
            return 0;
        }

        bool err = false;
        switch (e.id)
        {
        case 1:
            err = (e.args.size() != 1);
            break;
        case 2:
            err = (e.args.size() != 2);
            break;
        case 3:
            err = (e.args.size() != 1);
            break;
        case 4:
            err = (e.args.size() != 1);
            break;
        default:
            err = true;
        }
        if (err)
        {
            std::cout << line << std::endl;
            return 0;
        }

        club.processEvent(e);
        ++lineNo;
    }

    club.closeDay();
    club.printRes();
    return 0;
}