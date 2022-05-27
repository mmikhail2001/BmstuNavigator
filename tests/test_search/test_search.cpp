#include <gtest/gtest.h>

#include "points.h"
#include "db.h"

TEST(test_tools, test_true_1) {

    EXPECT_TRUE(true);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

