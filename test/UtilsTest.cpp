#include <gtest/gtest.h>

#include "src/lib/Utils.h"

TEST(UtilsTest, ShouldSplitStringIntoThreeParts){
    std::vector<std::string> parts = Utils::split("a,b,c", ',');

    EXPECT_EQ(parts[0], "a");
    EXPECT_EQ(parts[1], "b");
    EXPECT_EQ(parts[2], "c");

}

TEST(UtilsTest, ShouldRemoveWhiteSpace){
    std::string string = "   a b c   ";

    EXPECT_EQ(Utils::removeWhitespace(string), "abc");
}

TEST(UtilsTest, ShouldRemoveCommentInLine){
    std::string stringOne = "M=1 // this is a comment";
    std::string stringTwo = "@1 // this is a comment";

    EXPECT_EQ(Utils::removeComment(stringOne), "M=1 ");
    EXPECT_EQ(Utils::removeComment(stringTwo), "@1 ");
}

TEST(UtilsTest, ShouldReturnIsInt){
    EXPECT_TRUE(Utils::isInt("12345"));
    EXPECT_TRUE(Utils::isInt("1"));
    EXPECT_TRUE(Utils::isInt("999"));
}

TEST(UtilsTest, ShouldReturnIsNotInt){
    EXPECT_FALSE(Utils::isInt("123a4"));
    EXPECT_FALSE(Utils::isInt("abc: 123"));
    EXPECT_FALSE(Utils::isInt("0x1200"));
}

TEST(UtilsTest, ShouldReturnEndsWith){
    EXPECT_TRUE(Utils::endsWith("abc", "c"));
    EXPECT_TRUE(Utils::endsWith("ends with", "with"));
}

TEST(UtilsTest, ShouldNotReturnEndsWith){
    EXPECT_FALSE(Utils::endsWith("abc", "d"));
    EXPECT_FALSE(Utils::endsWith("ends with", "not"));
}