#include "Table.h"

Table::Table() : lastStart(0, 0), totalMinutes(0), income(0) {}

bool Table::isOccupied() const 
{
    return currentClient.has_value();
}

void Table::seat(const std::string& client, const ClubTime& time) 
{
    currentClient = client;
    lastStart = time;
}

void Table::leave(const ClubTime& time, int pricePerHour) 
{
    int duration = time.toMinutes() - lastStart.toMinutes();
    totalMinutes += duration;

    int hours = (duration + 59) / 60;
    income += hours * pricePerHour;

    currentClient.reset();
}

int Table::getTotalMinutes() const 
{
    return totalMinutes;
}

int Table::getIncome() const 
{
    return income;
}