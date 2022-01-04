#include <gtest/gtest.h>
#include <vector>

TEST(VectorTest, Clearing) {
    std::vector<int> vect{1, 2, 3};
    vect.clear();
    EXPECT_EQ(vect.empty(), true);
}