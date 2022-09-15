#include <gtest/gtest.h>

#include "src/lib/FileUtils.h"

TEST(FileUtilsTest, ShouldReadInFile){
    std::vector<std::string> fileContent = FileUtils::readInFile("test/resources/testfile.txt");

    EXPECT_EQ(fileContent.size(), 3);
    EXPECT_EQ(fileContent.at(0), "line1");
    EXPECT_EQ(fileContent.at(1), "line2");
    EXPECT_EQ(fileContent.at(2), "line3");
}