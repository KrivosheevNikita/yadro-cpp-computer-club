#include "Event.h"

#include <sstream>

Event Event::fromString(const std::string& line) 
{
    std::istringstream iss(line);
    std::string timeStr;
    int id;
    iss >> timeStr >> id;

    Event e;
    e.time = ClubTime::parse(timeStr);
    e.id = id;
    std::string arg;
    while (iss >> arg) 
        e.args.push_back(arg);

    return e;
}

std::string Event::toString() const 
{
    std::ostringstream oss;
    oss << time.toString() << ' ' << id;
    for (auto& a : args) 
        oss << ' ' << a;
    return oss.str();
}