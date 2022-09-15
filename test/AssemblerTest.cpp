#include <gtest/gtest.h>
#include <vector>
#include <iostream>

#include "src/lib/Assembler.h"

/*
 * Input:
 *   0: ___ // Comment
 *   1: M=1
 *
 * Output:
 *   0: M=1
 */
TEST(AssemblerTest, ShouldIgnoreComments){
    Assembler assembler;

    std::vector<std::string> inputProgram{
        "   // Comment\n",
        "M=1"};

    std::vector<std::string> withoutComment = assembler.resolveLabelSymbols(inputProgram);

    EXPECT_EQ(withoutComment.size(), 1);
    EXPECT_EQ(withoutComment.at(0), "M=1");
}

/*
 * Input:
 *   0: \n
 *   1: \t
 *   2: \r
 *   3: ______ (whitespaces)
 *   4: M=1
 * Output:
 *   0: M=1
 */
TEST(AssemblerTest, ShouldIgnoreEmptyLines){
    Assembler assembler;

    std::vector<std::string> program{
            "\n",
            "\t",
            "\r",
            "      ",
            "M=1"};

    std::vector<std::string> withoutComment = assembler.resolveLabelSymbols(program);

    EXPECT_EQ(withoutComment.size(), 1);
    EXPECT_EQ(withoutComment.at(0), "M=1");
}

/*
 * Input/Output:
 *   0: @0
 *   1: @1
 *   2: @20
 *   3: M=1
 */
TEST(AssemblerTest, ShouldNotMutateResolvedSymbols){
    Assembler assembler;

    std::vector<std::string> program{
        "@0",
        "@1",
        "@20",
        "M=1"
    };

    std::vector<std::string> resolvedPredefinedSymbols = assembler.resolveLabelSymbols(program);

    EXPECT_EQ(resolvedPredefinedSymbols.size(), 4);

    EXPECT_EQ(resolvedPredefinedSymbols.at(0), "@0");
    EXPECT_EQ(resolvedPredefinedSymbols.at(1), "@1");
    EXPECT_EQ(resolvedPredefinedSymbols.at(2), "@20");
    EXPECT_EQ(resolvedPredefinedSymbols.at(3), "M=1");
}

/*
 * Input:
 *   (LOOP)
 *   0: @1
 *   1: M=1
 *   2: @LOOP
 *   3: 0;JGE
 *
 * Output:
 *   0: @1
 *   1: M=1
 *   2: @0
 *   3: 0;JGE
 */


TEST(AssemblerTest, ShouldResolveLabelSymbols){
    Assembler assembler;

    std::vector<std::string> program{
            "(LOOP)",
            "@1",
            "M=1",
            "@LOOP",
            "0;JGE"
    };

    std::vector<std::string> resolvedPredefinedSymbols = assembler.resolveLabelSymbols(program);

    EXPECT_EQ(resolvedPredefinedSymbols.size(), 4);

    EXPECT_EQ(resolvedPredefinedSymbols.at(0), "@1");
    EXPECT_EQ(resolvedPredefinedSymbols.at(1), "M=1");
    EXPECT_EQ(resolvedPredefinedSymbols.at(2), "@0");
    EXPECT_EQ(resolvedPredefinedSymbols.at(3), "0;JGE");
}

/*
 * Input (without indirect symbols):
 *   @21
 *   MD=D+1
 *   MD=A-1;JGE
 *
 * Output:
 *   0000000000010101
 *   1110011111011000
 *   1110110010011011
 */

TEST(AssemblerTest, ShouldTranslateProgramWithResolvedSymbols){
    Assembler assembler;

    std::vector<std::string> program{
        "@21",
        "MD=D+1",
        "MD=A-1;JGE"
    };

    std::vector<std::string> translatedProgram = assembler.translateToBinary(program);

    EXPECT_EQ(translatedProgram.size(), 3);

    EXPECT_EQ(translatedProgram.at(0), "0000000000010101");
    EXPECT_EQ(translatedProgram.at(1), "1110011111011000");
    EXPECT_EQ(translatedProgram.at(2), "1110110010011011");
}

TEST(AssemblerTest, ShouldTranslateBiggerProgramWithResolvedSymbols){
    Assembler assembler;

    std::vector<std::string> program{
            "@16",
            "M=1",
            "@17",
            "M=0",
            "@16",
            "D=M",
            "@0",
            "D=D-M",
            "@18",
            "D;JGT",
            "@16",
            "D=M",
            "@17",
            "M=D+M",
            "@16",
            "M=M+1",
            "@4",
            "0;JMP",
            "@17",
            "D=M",
            "@1",
            "M=D",
            "@22",
            "0;JMP",
    };

    std::vector<std::string> translatedProgram = assembler.translateToBinary(program);

    EXPECT_EQ(translatedProgram.size(), 24);

    EXPECT_EQ(translatedProgram.at(0), "0000000000010000");
    EXPECT_EQ(translatedProgram.at(1), "1110111111001000");
    EXPECT_EQ(translatedProgram.at(2), "0000000000010001");
    EXPECT_EQ(translatedProgram.at(3), "1110101010001000");
    EXPECT_EQ(translatedProgram.at(4), "0000000000010000");
    EXPECT_EQ(translatedProgram.at(5), "1111110000010000");
    EXPECT_EQ(translatedProgram.at(6), "0000000000000000");
    EXPECT_EQ(translatedProgram.at(7), "1111010011010000");
    EXPECT_EQ(translatedProgram.at(8), "0000000000010010");
    EXPECT_EQ(translatedProgram.at(9), "1110001100000001");
    EXPECT_EQ(translatedProgram.at(10), "0000000000010000");
    EXPECT_EQ(translatedProgram.at(11), "1111110000010000");
    EXPECT_EQ(translatedProgram.at(12), "0000000000010001");
    EXPECT_EQ(translatedProgram.at(13), "1111000010001000");
    EXPECT_EQ(translatedProgram.at(14), "0000000000010000");
    EXPECT_EQ(translatedProgram.at(15), "1111110111001000");
    EXPECT_EQ(translatedProgram.at(16), "0000000000000100");
    EXPECT_EQ(translatedProgram.at(17), "1110101010000111");
    EXPECT_EQ(translatedProgram.at(18), "0000000000010001");
    EXPECT_EQ(translatedProgram.at(19), "1111110000010000");
    EXPECT_EQ(translatedProgram.at(20), "0000000000000001");
    EXPECT_EQ(translatedProgram.at(21), "1110001100001000");
    EXPECT_EQ(translatedProgram.at(22), "0000000000010110");
    EXPECT_EQ(translatedProgram.at(23), "1110101010000111");
}

/*
 * Sample program from https://www.nand2tetris.org/_files/ugd/44046b_89a8e226476741a3b7c5204575b8a0b2.pdf (Page 9)
 */
TEST(Assembler, ShouldAssembleAdditionProgram){
    Assembler assembler;

    std::vector<std::string> program{
        "// Adds 1 + ... + 100",
        "    @i",
        "    M=1    // i=1",
        "    @sum",
        "    M=0    // sum=0",
        "(LOOP)",
        "    @i",
        "    D=M    // D=i",
        "    @100",
        "    D=D-A  // D=i-100",
        "    @END",
        "    D;JGT  // if (i-100)>0 goto END",
        "    @i",
        "    D=M    // D=i",
        "    @sum",
        "    M=D+M  // sum=sum+i",
        "    @i",
        "    M=M+1  // i=i+1",
        "    @LOOP",
        "    0;JMP  // goto LOOP",
        "(END)",
        "    @END",
        "    0;JMP  // infinite loop",
    };

    std::vector<std::string> translatedProgram = assembler.assemble(program);

    EXPECT_EQ(translatedProgram.size(), 20);

    EXPECT_EQ(translatedProgram.at(0), "0000000000010000");
    EXPECT_EQ(translatedProgram.at(1), "1110111111001000");
    EXPECT_EQ(translatedProgram.at(2), "0000000000010001");
    EXPECT_EQ(translatedProgram.at(3), "1110101010001000");
    EXPECT_EQ(translatedProgram.at(4), "0000000000010000");
    EXPECT_EQ(translatedProgram.at(5), "1111110000010000");
    EXPECT_EQ(translatedProgram.at(6), "0000000001100100");
    EXPECT_EQ(translatedProgram.at(7), "1110010011010000");
    EXPECT_EQ(translatedProgram.at(8), "0000000000010010");
    EXPECT_EQ(translatedProgram.at(9), "1110001100000001");
    EXPECT_EQ(translatedProgram.at(10), "0000000000010000");
    EXPECT_EQ(translatedProgram.at(11), "1111110000010000");
    EXPECT_EQ(translatedProgram.at(12), "0000000000010001");
    EXPECT_EQ(translatedProgram.at(13), "1111000010001000");
    EXPECT_EQ(translatedProgram.at(14), "0000000000010000");
    EXPECT_EQ(translatedProgram.at(15), "1111110111001000");
    EXPECT_EQ(translatedProgram.at(16), "0000000000000100");
    EXPECT_EQ(translatedProgram.at(17), "1110101010000111");
    EXPECT_EQ(translatedProgram.at(18), "0000000000010010");
    EXPECT_EQ(translatedProgram.at(19), "1110101010000111");
}

/*
 * Sample file from nand2tetris ("Max")
 */
TEST(AssemblerTest, ShouldAssembleMaxProgram){
    Assembler assembler;

    std::vector<std::string> program{
            "// This file is part of www.nand2tetris.org",
            "// and the book \"The Elements of Computing Systems\"",
           "// by Nisan and Schocken, MIT Press.",
            "// File name: projects/06/max/Max.asm",
            "",
            "// Computes R2 = max(R0, R1)  (R0,R1,R2 refer to RAM[0],RAM[1],RAM[2])",
            "",
            "@R0",
            "D=M              // D = first number",
            "@R1",
            "D=D-M            // D = first number - second number",
            "@OUTPUT_FIRST",
            "D;JGT            // if D>0 (first is greater) goto output_first",
            "@R1",
            "D=M              // D = second number",
            "@OUTPUT_D",
            "0;JMP            // goto output_d",
            "(OUTPUT_FIRST)",
            "@R0",
            "D=M              // D = first number",
            "(OUTPUT_D)",
            "@R2",
            "M=D              // M[2] = D (greatest number)",
            "(INFINITE_LOOP)",
            "@INFINITE_LOOP",
            "0;JMP            // infinite loop"
    };


    std::vector<std::string> translatedProgram = assembler.assemble(program);

    EXPECT_EQ(translatedProgram.size(), 16);
    EXPECT_EQ(translatedProgram.at(0), "0000000000000000");
    EXPECT_EQ(translatedProgram.at(1), "1111110000010000");
    EXPECT_EQ(translatedProgram.at(2), "0000000000000001");
    EXPECT_EQ(translatedProgram.at(3), "1111010011010000");
    EXPECT_EQ(translatedProgram.at(4), "0000000000001010");
    EXPECT_EQ(translatedProgram.at(5), "1110001100000001");
    EXPECT_EQ(translatedProgram.at(6), "0000000000000001");
    EXPECT_EQ(translatedProgram.at(7), "1111110000010000");
    EXPECT_EQ(translatedProgram.at(8), "0000000000001100");
    EXPECT_EQ(translatedProgram.at(9), "1110101010000111");
    EXPECT_EQ(translatedProgram.at(10), "0000000000000000");
    EXPECT_EQ(translatedProgram.at(11), "1111110000010000");
    EXPECT_EQ(translatedProgram.at(12), "0000000000000010");
    EXPECT_EQ(translatedProgram.at(13), "1110001100001000");
    EXPECT_EQ(translatedProgram.at(14), "0000000000001110");
    EXPECT_EQ(translatedProgram.at(15), "1110101010000111");
}