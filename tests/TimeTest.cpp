#include "ClubTime.h"

#include <gtest/gtest.h>

TEST(Time_Parse_Valid, Simple) 
{
    auto t = ClubTime::parse("00:00");
    EXPECT_EQ(t.hours, 0);
    EXPECT_EQ(t.minutes, 0);
    EXPECT_EQ(t.toString(), "00:00");
}

TEST(Time_Parse_Valid, Midday) 
{
    auto t = ClubTime::parse("12:34");
    EXPECT_EQ(t.hours, 12);
    EXPECT_EQ(t.minutes, 34);
    EXPECT_EQ(t.toString(), "12:34");
    EXPECT_EQ(t.toMinutes(), 12 * 60 + 34);
}

TEST(Time_Parse_InvalidFormat, BadSeparator) 
{
    EXPECT_THROW(ClubTime::parse("1234"), std::runtime_error);
}

TEST(Time_Parse_InvalidValue, HourOverflow) 
{
    EXPECT_THROW(ClubTime::parse("24:00"), std::runtime_error);
}
