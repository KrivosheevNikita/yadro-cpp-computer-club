#ifndef TABLE_H
#define TABLE_H

#include "ClubTime.h"
#include <optional>
#include <string>

// Состояние одного стола
class Table {
public:
    Table();

    // Проверяем, занят ли стол
    bool isOccupied() const;

    // Садим клиента за стол и фиксируем время начала
    void seat(const std::string& client, const ClubTime& time);

    // Когда клиент уходит, то обновляем занятость и выручку
    void leave(const ClubTime& time, int pricePerHour);

    // Общее время занятности стола
    int getTotalMinutes() const;

    // Получить общую выручку за день для этого стола
    int getIncome() const;

private:
    std::optional<std::string> currentClient; 
    ClubTime lastStart;               
    int totalMinutes;                         
    int income;                             
};

#endif