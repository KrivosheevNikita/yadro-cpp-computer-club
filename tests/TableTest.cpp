#include "Table.h"
#include <gtest/gtest.h>

TEST(Table_SeatAndLeave_SingleHour, RevenueAndTime) 
{
    Table tbl;
    tbl.seat("client", ClubTime::parse("10:00"));
    tbl.leave(ClubTime::parse("11:00"), 50);
    EXPECT_EQ(tbl.getTotalMinutes(), 60);
    EXPECT_EQ(tbl.getIncome(), 50);
}

TEST(Table_SeatAndLeave_PartialHour, RoundUp) 
{
    Table tbl;
    tbl.seat("client", ClubTime::parse("08:10"));
    tbl.leave(ClubTime::parse("08:20"), 20);
    EXPECT_EQ(tbl.getTotalMinutes(), 10);
    EXPECT_EQ(tbl.getIncome(), 20);
}

TEST(Table_MultipleSessions, Accumulate) 
{
    Table tbl;
    tbl.seat("client", ClubTime::parse("09:00"));
    tbl.leave(ClubTime::parse("09:30"), 30);
    tbl.seat("client", ClubTime::parse("10:00"));
    tbl.leave(ClubTime::parse("11:15"), 30);
    EXPECT_EQ(tbl.getTotalMinutes(), 30 + 75);
    EXPECT_EQ(tbl.getIncome(), 30 + 60);
}

TEST(Table_IsOccupied, Status) 
{
    Table tbl;
    EXPECT_FALSE(tbl.isOccupied());
    tbl.seat("client", ClubTime::parse("12:00"));
    EXPECT_TRUE(tbl.isOccupied());
    tbl.leave(ClubTime::parse("12:01"), 10);
    EXPECT_FALSE(tbl.isOccupied());
}