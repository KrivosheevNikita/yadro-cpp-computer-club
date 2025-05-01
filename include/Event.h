#ifndef EVENT_H
#define EVENT_H

#include "ClubTime.h"

#include <string>
#include <vector>

// ��������� ������� (�����, id, ���������)
class Event {
public:
    ClubTime time;              
    int id;                    
    std::vector<std::string> args; 

    // ������� Event �� ������
    static Event fromString(const std::string& line);

    // ����������� Event ������� � ������ ��� ������
    std::string toString() const;
};

#endif
