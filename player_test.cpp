#include "player.h"
#include <gtest/gtest.h>

TEST(PlayerTest, Getters) {
    // Test the getters
    Player player(1, "testuser", "testpassword", QImage());
    EXPECT_EQ(player.getId(), 1);
    EXPECT_EQ(player.getUsername(), "testuser");
    EXPECT_EQ(player.getHashedPassword(), "testpassword");
}

// Add more test cases as needed
