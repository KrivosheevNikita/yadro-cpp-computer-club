#include "Club.h"

#include <algorithm>
#include <iostream>
#include <iomanip>

Club::Club(int tableCount, ClubTime open, ClubTime close, int price)
    : pricePerHour(price), openTime(open), closeTime(close), tables(tableCount) {}

void Club::errorEvent(const ClubTime& time, const std::string& message) 
{
    outputEvents.push_back(Event{ time, 13, {message} });
}

void Club::generateLeaveEvent(const ClubTime& time, const std::string& client) 
{
    outputEvents.push_back(Event{ time, 11, {client} });
}

void Club::generateSeatEvent(const ClubTime& time, const std::string& client, int tableIndex) 
{
    outputEvents.push_back(Event{ time, 12, {client, std::to_string(tableIndex)} });
}

void Club::processEvent(const Event& e) 
{
    outputEvents.push_back(e);
    const auto& args = e.args;
    std::string name;
    int tableIdx;
    switch (e.id) 
    {
    case 1:
        name = args[0];
        if (clientsInClub.count(name))
            errorEvent(e.time, "YouShallNotPass");
        else if (e.time < openTime || e.time >= closeTime)
            errorEvent(e.time, "NotOpenYet");
        else 
        {
            clientsInClub.insert(name);
            clientTable[name] = 0;
        }
        break;

    case 2:
        name = args[0];
        tableIdx = std::stoi(args[1]);
        if (!clientsInClub.count(name))
            errorEvent(e.time, "ClientUnknown");
        else if (tableIdx < 1 || tableIdx > tables.size() || tables[tableIdx - 1].isOccupied())
            errorEvent(e.time, "PlaceIsBusy");
        else 
        {
            int old = clientTable[name];
            if (old > 0) 
            {
                tables[old - 1].leave(e.time, pricePerHour);
                clientTable[name] = 0;
                if (!waitQueue.empty()) 
                {
                    std::string next = waitQueue.front(); waitQueue.pop_front();
                    generateSeatEvent(e.time, next, old);
                    tables[old - 1].seat(next, e.time);
                    clientTable[next] = old;
                }
            }
            tables[tableIdx - 1].seat(name, e.time);
            clientTable[name] = tableIdx;
        }
        break;

    case 3:
        name = args[0];
        {
            bool freeTable = false;
            for (const auto& t : tables)
            {
                if (!t.isOccupied())
                {
                    freeTable = true;
                    break;
                }
            }
            if (freeTable)
                errorEvent(e.time, "ICanWaitNoLonger!");
            else if (waitQueue.size() >= tables.size())
                generateLeaveEvent(e.time, name);
            else
                waitQueue.push_back(name);
        }
        break;

    case 4:
        name = args[0];
        if (!clientsInClub.count(name))
            errorEvent(e.time, "ClientUnknown");
        else 
        {
            int oldT = clientTable[name];
            if (oldT > 0) 
            {
                tables[oldT - 1].leave(e.time, pricePerHour);
                clientTable[name] = 0;
                if (!waitQueue.empty()) 
                {
                    std::string next = waitQueue.front(); waitQueue.pop_front();
                    generateSeatEvent(e.time, next, oldT);
                    tables[oldT - 1].seat(next, e.time);
                    clientTable[next] = oldT;
                }
            }
            else 
            {
                auto it = std::find(waitQueue.begin(), waitQueue.end(), name);
                if (it != waitQueue.end()) 
                    waitQueue.erase(it);
            }
            generateLeaveEvent(e.time, name);
            clientsInClub.erase(name);
        }
        break;

    default:
        break;
    }
}

void Club::closeDay() 
{
    std::vector<std::string> remaining(clientsInClub.begin(), clientsInClub.end());
    std::sort(remaining.begin(), remaining.end());
    for (const auto& name : remaining) 
    {
        int oldT = clientTable[name];
        if (oldT > 0) 
        {
            tables[oldT - 1].leave(closeTime, pricePerHour);
            clientTable[name] = 0;
        }
        generateLeaveEvent(closeTime, name);
    }
    clientsInClub.clear();
    waitQueue.clear();
}

void Club::printRes() const 
{
    std::cout << openTime.toString() << std::endl;
    for (const auto& e : outputEvents) 
        std::cout << e.toString() << std::endl;
    std::cout << closeTime.toString() << std::endl;

    for (int i = 0; i != tables.size(); ++i) 
    {
        const auto& t = tables[i];
        int tm = t.getTotalMinutes();
        int h = tm / 60;
        int m = tm % 60;
        std::cout << (i + 1) << " " << t.getIncome() << " "
            << std::setw(2) << std::setfill('0') << h << ":"
            << std::setw(2) << std::setfill('0') << m << std::endl;
    }
}