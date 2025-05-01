#ifndef TABLE_H
#define TABLE_H

#include "ClubTime.h"
#include <optional>
#include <string>

// ��������� ������ �����
class Table {
public:
    Table();

    // ���������, ����� �� ����
    bool isOccupied() const;

    // ����� ������� �� ���� � ��������� ����� ������
    void seat(const std::string& client, const ClubTime& time);

    // ����� ������ ������, �� ��������� ��������� � �������
    void leave(const ClubTime& time, int pricePerHour);

    // ����� ����� ���������� �����
    int getTotalMinutes() const;

    // �������� ����� ������� �� ���� ��� ����� �����
    int getIncome() const;

private:
    std::optional<std::string> currentClient; 
    ClubTime lastStart;               
    int totalMinutes;                         
    int income;                             
};

#endif