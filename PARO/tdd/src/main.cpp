#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <unordered_map>

TEST(EnvironmentTest, FailTest) {
    EXPECT_EQ(1, 2);
}

struct stock {
	bool countable;
	std::string name;
	double price;
	double quantity;
};


TEST(EnvironmentTest, structTest) {
	stock s;
	s.countable = true;
	s.name = "apple";
	s.price = 1.0;
	s.quantity = 10.0;
	EXPECT_EQ(s.countable, true);
	EXPECT_EQ(s.name, "apple");
	EXPECT_EQ(s.price, 1.0);
	EXPECT_EQ(s.quantity, 10.0);
}
