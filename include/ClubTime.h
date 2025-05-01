#ifndef CLUBTIME_H
#define CLUBTIME_H

#include <string>

// Класс для работы со временем
class ClubTime {
public:
    // Задает часы и минуты
    ClubTime(int h = 0, int m = 0);

    // Парсинг строки XX:XX в объект ClubTime
    static ClubTime parse(const std::string& str);

    // Возвращает общее количество минут с начала дня
    int toMinutes() const;

    // Преобразует время в строку XX:XX
    std::string toString() const;

    bool operator<(const ClubTime& other) const;
    bool operator<=(const ClubTime& other) const;
    bool operator==(const ClubTime& other) const;
    bool operator>(const ClubTime& other) const;
    bool operator>=(const ClubTime& other) const;
    bool operator!=(const ClubTime& other) const;

    int hours; 
    int minutes;
};

#endif