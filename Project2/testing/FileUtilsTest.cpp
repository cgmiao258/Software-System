#include "gtest/gtest.h"
#include "FileUtils.h"

TEST(FileUtilsTest, IsFileExists){
    FileUtils fileUtils;
    std::ifstream file("none.csv");
    EXPECT_FALSE(fileUtils.IsFileExists(file));
    if (file.is_open()) {
        file.close();
    }

    std::ifstream file2("./testing/test_IR.csv");
    EXPECT_TRUE(fileUtils.IsFileExists(file2));
    if (file2.is_open()) {
        file2.close();
    }
}