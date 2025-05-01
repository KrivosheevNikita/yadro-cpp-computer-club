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

    try 
    {
        int n, price;
        std::string openStr, closeStr, line;
        std::getline(file, line); 
        n = std::stoi(line);
        std::getline(file, line); 
        std::istringstream(line) >> openStr >> closeStr;
        std::getline(file, line); 
        price = std::stoi(line);

        Club club(n, ClubTime::parse(openStr), ClubTime::parse(closeStr), price);
        while (std::getline(file, line)) 
        {
            if (line.empty()) 
                continue;
            Event e = Event::fromString(line);
            club.processEvent(e);
        }

        club.closeDay();
        club.printRes();

    }
    catch (const std::exception& e) 
    {
        std::cout << e.what() << std::endl;
        return 0;
    }

    return 0;
}