#ifndef CLUB_H
#define CLUB_H

#include "Event.h"
#include "Table.h"

#include <vector>
#include <deque>
#include <unordered_map>
#include <set>

// �������� ������ �����
class Club {
public:
    Club(int tableCount, ClubTime openTime, ClubTime closeTime, int pricePerHour);

    // ������������ �������� �������
    void processEvent(const Event& e);

    // ���������� ������� ����� ���� ��������
    void closeDay();

    // ������� ������� � ���������� �� ������
    void printRes() const;

private:
    int pricePerHour;                
    ClubTime openTime, closeTime;    
    std::vector<Table> tables;      
    std::set<std::string> clientsInClub; 
    std::unordered_map<std::string, int> clientTable; 
    std::deque<std::string> waitQueue;   
    std::vector<Event> outputEvents;     

    // ��������� ������, id 13
    void errorEvent(const ClubTime& time, const std::string& message);

    // ��������� ������� ����� �� �����, id 11
    void generateLeaveEvent(const ClubTime& time, const std::string& client);

    // ��������� ������� ������� �� �������, id 12
    void generateSeatEvent(const ClubTime& time, const std::string& client, int tableIndex);
};


#endif 