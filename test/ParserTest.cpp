#include <gtest/gtest.h>
#include "src/lib/Parser.h"

TEST(ParserTest, ShouldReturnIsAInstruction){
    Parser parser;

    std::string aInstruction = "@21";

    EXPECT_TRUE(parser.isAInstruction(aInstruction));
}

TEST(ParserTest, ShouldReturnIsNotAnAInstruction){
    Parser parser;

    std::string notAnAInstruction = "JMP;0";

    EXPECT_FALSE(parser.isAInstruction(notAnAInstruction));
}

TEST(ParserTest, ShouldReturnParsedCInstructionWithDestJumpAndComp){
    Parser parser;

    std::string rawCInstruction = "D = M + 1; JGT // this is a comment";
    CInstruction parsedCInstruction = parser.parseCInstruction(rawCInstruction);

    EXPECT_EQ(parsedCInstruction.dest, "D");
    EXPECT_EQ(parsedCInstruction.comp, "M+1");
    EXPECT_EQ(parsedCInstruction.jump, "JGT");
}

TEST(ParserTest, ShouldReturnParsedCInstructionWithDestAndComp){
    Parser parser;

    std::string rawCInstruction = "M=0";
    CInstruction parsedCInstruction = parser.parseCInstruction(rawCInstruction);

    EXPECT_EQ(parsedCInstruction.dest, "M");
    EXPECT_EQ(parsedCInstruction.comp, "0");
    EXPECT_EQ(parsedCInstruction.jump, "");
}

TEST(ParserTest, ShouldReturnParsedCInstructionWithCompAndJump){
    Parser parser;

    std::string rawCInstruction = "0;JMP";
    CInstruction parsedCInstruction = parser.parseCInstruction(rawCInstruction);

    EXPECT_EQ(parsedCInstruction.dest, "");
    EXPECT_EQ(parsedCInstruction.comp, "0");
    EXPECT_EQ(parsedCInstruction.jump, "JMP");
}

TEST(ParserTest, ShouldReturnIsComment){
    Parser parser;

    EXPECT_TRUE(parser.isComment("// this is a comment"));
    EXPECT_TRUE(parser.isComment("// D=M"));
    EXPECT_TRUE(parser.isComment("// 0;JGT"));
}

TEST(ParserTest, ShouldReturnIsNotAComment){
    Parser parser;

    EXPECT_FALSE(parser.isComment("M=1"));
    EXPECT_FALSE(parser.isComment("M=1 // this is a comment"));
}

TEST(ParserTest, ShouldReturnIsEmptyLine){
    Parser parser;

    EXPECT_TRUE(parser.isEmptyLine(""));
    EXPECT_TRUE(parser.isEmptyLine("   "));
    EXPECT_TRUE(parser.isEmptyLine("   \n"));
    EXPECT_TRUE(parser.isEmptyLine("   \r"));
    EXPECT_TRUE(parser.isEmptyLine("   \t"));
    EXPECT_TRUE(parser.isEmptyLine("   \n\r\t"));
}

TEST(ParserTest, ShouldReturnIsNotAnEmptyLine){
    Parser parser;

    EXPECT_FALSE(parser.isEmptyLine("abc"));
    EXPECT_FALSE(parser.isEmptyLine("       a"));
    EXPECT_FALSE(parser.isEmptyLine("       d\n"));
}

TEST(ParserTest, ShouldReturnIsLabelSymbol){
    Parser parser;

    EXPECT_TRUE(parser.isLabelSymbol("(LOOP) // this is a comment"));
    EXPECT_TRUE(parser.isLabelSymbol("   (LOOP)   "));
    EXPECT_TRUE(parser.isLabelSymbol("  (LOOP)  "));
}

TEST(ParserTest, ShouldReturnIsNotALabelSymbol){
    Parser parser;

    EXPECT_FALSE(parser.isLabelSymbol("M=1"));
    EXPECT_FALSE(parser.isLabelSymbol("0;JGT"));
    EXPECT_FALSE(parser.isLabelSymbol("M=1;JNE"));
}

TEST(ParserTest, ShouldReturnIsPredefinedSymbol){
    Parser parser;

    EXPECT_TRUE(parser.isPredefinedSymbol("R0"));
    EXPECT_TRUE(parser.isPredefinedSymbol("KBD"));
    EXPECT_TRUE(parser.isPredefinedSymbol("THIS"));
}

TEST(ParserTest, ShouldReturnIsNotAPredefinedSymbol){
    Parser parser;

    EXPECT_FALSE(parser.isPredefinedSymbol("@1"));
    EXPECT_FALSE(parser.isPredefinedSymbol("@R20"));
    EXPECT_FALSE(parser.isPredefinedSymbol("KEYBOARD"));
}

TEST(ParserTest, ShouldParseAInstruction){
    Parser parser;
    std::string instruction = "@i   // this is a comment";

    EXPECT_EQ(parser.parseAInstruction(instruction), "i");
}

TEST(ParserTest, ShouldParseLabelSymbol){
    Parser parser;

    EXPECT_EQ(parser.parseLabelSymbol("(LOOP)"), "LOOP");
    EXPECT_EQ(parser.parseLabelSymbol(" ( LOOP ) "), "LOOP");
    EXPECT_EQ(parser.parseLabelSymbol("(LOOP) // this is a comment"), "LOOP");
}