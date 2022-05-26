#include <iostream>
// #include <sys/sysinfo.h>
#include <gtest/gtest.h>
#include "gmock/gmock.h"

// using ::testing::AtLeast;
// using ::testing::DoAll;
// using ::testing::Return;
// using ::testing::SetArgReferee;

#include "tg_bot.h"
#include "points.h"
#include "db.h"

TEST(test_tools, test_create_keyboards) {

    EXPECT_TRUE(true);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}