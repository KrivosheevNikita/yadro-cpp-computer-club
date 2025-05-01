#ifndef EVENT_H
#define EVENT_H

#include "ClubTime.h"

#include <string>
#include <vector>

// Структура события (время, id, аргументы)
class Event {
public:
    ClubTime time;              
    int id;                    
    std::vector<std::string> args; 

    // Создает Event из строки
    static Event fromString(const std::string& line);

    // Преобразует Event обратно в строку для вывода
    std::string toString() const;
};

#endif
