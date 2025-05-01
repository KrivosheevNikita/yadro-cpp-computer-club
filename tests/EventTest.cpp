#include "Event.h"

#include <gtest/gtest.h>

TEST(Event_FromString_Valid, NoArgs) 
{
    auto e = Event::fromString("09:00 1");
    EXPECT_EQ(e.time.toString(), "09:00");
    EXPECT_EQ(e.id, 1);
    EXPECT_TRUE(e.args.empty());
}

TEST(Event_FromString_Valid, WithArgs) 
{
    auto e = Event::fromString("10:15 2 client1 3");
    EXPECT_EQ(e.time.toString(), "10:15");
    EXPECT_EQ(e.id, 2);
    ASSERT_EQ(e.args.size(), 2u);
    EXPECT_EQ(e.args[0], "client1");
    EXPECT_EQ(e.args[1], "3");
    EXPECT_EQ(e.toString(), "10:15 2 client1 3");
}

TEST(Event_FromString_InvalidTime, Throws) 
{
    EXPECT_THROW(Event::fromString("9:00 1 client"), std::runtime_error);
}
