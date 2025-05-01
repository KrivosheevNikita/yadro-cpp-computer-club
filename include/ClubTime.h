#ifndef CLUBTIME_H
#define CLUBTIME_H

#include <string>

// ����� ��� ������ �� ��������
class ClubTime {
public:
    // ������ ���� � ������
    ClubTime(int h = 0, int m = 0);

    // ������� ������ XX:XX � ������ ClubTime
    static ClubTime parse(const std::string& str);

    // ���������� ����� ���������� ����� � ������ ���
    int toMinutes() const;

    // ����������� ����� � ������ XX:XX
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