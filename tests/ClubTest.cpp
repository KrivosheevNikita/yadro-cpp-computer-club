#include "ClubTime.h"
#include "Event.h"
#include "Club.h"
#include <gtest/gtest.h>
#include <string>

using ::testing::internal::CaptureStdout;
using ::testing::internal::GetCapturedStdout;

TEST(Club, NotOpenYet) 
{
    Club club(
        1,
        ClubTime::parse("09:00"),
        ClubTime::parse("10:00"),
        10
    );
    CaptureStdout();
    club.processEvent(Event::fromString("08:00 1 client1"));
    club.closeDay();
    club.printRes();
    std::string out = GetCapturedStdout();
    EXPECT_NE(out.find("08:00 13 NotOpenYet"), std::string::npos);
}

TEST(Club, SimpleSeatAndLeave) 
{
    Club club(
        1,
        ClubTime::parse("09:00"),
        ClubTime::parse("11:00"),
        15
    );
    CaptureStdout();
    club.processEvent(Event::fromString("09:05 1 client"));
    club.processEvent(Event::fromString("09:10 2 client 1"));
    club.processEvent(Event::fromString("10:00 4 client"));
    club.closeDay();
    club.printRes();
    std::string out = GetCapturedStdout();
    EXPECT_NE(out.find("1 15 00:50"), std::string::npos);
}

TEST(Club, PlaceIsBusy) 
{
    Club club(
        1,
        ClubTime::parse("09:00"),
        ClubTime::parse("12:00"),
        20
    );
    CaptureStdout();
    club.processEvent(Event::fromString("09:00 1 client1"));
    club.processEvent(Event::fromString("09:05 2 client1 1"));
    club.processEvent(Event::fromString("09:10 1 client2"));
    club.processEvent(Event::fromString("09:12 2 client2 1"));
    club.closeDay();
    club.printRes();
    std::string out = GetCapturedStdout();
    EXPECT_NE(out.find("09:12 13 PlaceIsBusy"), std::string::npos);
}

TEST(Club, WaitingQueueOverflow) 
{
    Club club(
        1,
        ClubTime::parse("08:00"),
        ClubTime::parse("10:00"),
        5
    );
    CaptureStdout();
    club.processEvent(Event::fromString("08:00 1 u1"));
    club.processEvent(Event::fromString("08:01 2 u1 1"));
    club.processEvent(Event::fromString("08:02 1 u2"));
    club.processEvent(Event::fromString("08:03 3 u2"));
    club.processEvent(Event::fromString("08:04 1 u3"));
    club.processEvent(Event::fromString("08:05 3 u3"));
    club.closeDay();
    club.printRes();
    std::string out = GetCapturedStdout();
    EXPECT_NE(out.find("08:05 11 u3"), std::string::npos);
}

TEST(Club, AutoSeatFromQueue) 
{
    Club club(
        1,
        ClubTime::parse("09:00"),
        ClubTime::parse("11:00"),
        10
    );
    CaptureStdout();
    club.processEvent(Event::fromString("09:00 1 c1"));
    club.processEvent(Event::fromString("09:01 2 c1 1"));
    club.processEvent(Event::fromString("09:02 1 c2"));
    club.processEvent(Event::fromString("09:03 3 c2"));
    club.processEvent(Event::fromString("09:10 4 c1"));
    club.closeDay();
    club.printRes();
    std::string out = GetCapturedStdout();
    EXPECT_NE(out.find("09:10 12 c2 1"), std::string::npos);
}
