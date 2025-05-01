#include "ClubTime.h"

#include <sstream>
#include <iomanip>
#include <stdexcept>

ClubTime::ClubTime(int h, int m) : hours(h), minutes(m) {}

ClubTime ClubTime::parse(const std::string& str) 
{
    if (str.size() != 5 || str[2] != ':')
        throw std::runtime_error("Invalid format time");

    int h = std::stoi(str.substr(0, 2));
    int m = std::stoi(str.substr(3, 2));

    if (h < 0 || h > 23 || m < 0 || m > 59)
        throw std::runtime_error("Invalid time value");

    return ClubTime(h, m);
}

int ClubTime::toMinutes() const 
{
    return hours * 60 + minutes;
}

std::string ClubTime::toString() const 
{
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hours << ':' 
        << std::setw(2) << std::setfill('0') << minutes;
    return oss.str();
}

bool ClubTime::operator<(const ClubTime& other) const 
{
    return toMinutes() < other.toMinutes();
}

bool ClubTime::operator<=(const ClubTime& other) const 
{
    return toMinutes() <= other.toMinutes();
}

bool ClubTime::operator==(const ClubTime& other) const 
{
    return toMinutes() == other.toMinutes();
}

bool ClubTime::operator>(const ClubTime& other) const 
{
    return other < *this;
}

bool ClubTime::operator>=(const ClubTime& other) const 
{
    return other <= *this;
}

bool ClubTime::operator!=(const ClubTime& other) const 
{
    return !(*this == other);
}
