#include <gtest/gtest.h>
#include "src/lib/SymbolTable.h"

TEST(SymbolTableTest, ShouldReturnKeyExists){
    SymbolTable symbolTable;

    symbolTable.add("a", 1);

    EXPECT_TRUE(symbolTable.exists("a"));
}

TEST(SymbolTableTest, ShouldReturnKeyDoesntExist){
    SymbolTable symbolTable;

    EXPECT_FALSE(symbolTable.exists("a"));
}

TEST(SymbolTable, ShouldContainAllPredefinedSymbols){
    SymbolTable symbolTable;

    EXPECT_TRUE(symbolTable.exists("R0"));
    EXPECT_TRUE(symbolTable.exists("R1"));
    EXPECT_TRUE(symbolTable.exists("R2"));
    EXPECT_TRUE(symbolTable.exists("R3"));
    EXPECT_TRUE(symbolTable.exists("R4"));
    EXPECT_TRUE(symbolTable.exists("R5"));
    EXPECT_TRUE(symbolTable.exists("R6"));
    EXPECT_TRUE(symbolTable.exists("R7"));
    EXPECT_TRUE(symbolTable.exists("R8"));
    EXPECT_TRUE(symbolTable.exists("R9"));
    EXPECT_TRUE(symbolTable.exists("R10"));
    EXPECT_TRUE(symbolTable.exists("R11"));
    EXPECT_TRUE(symbolTable.exists("R12"));
    EXPECT_TRUE(symbolTable.exists("R13"));
    EXPECT_TRUE(symbolTable.exists("R14"));
    EXPECT_TRUE(symbolTable.exists("R15"));

    EXPECT_TRUE(symbolTable.exists("SCREEN"));
    EXPECT_TRUE(symbolTable.exists("KBD"));

    EXPECT_TRUE(symbolTable.exists("SP"));
    EXPECT_TRUE(symbolTable.exists("LCL"));
    EXPECT_TRUE(symbolTable.exists("ARG"));
    EXPECT_TRUE(symbolTable.exists("THIS"));
    EXPECT_TRUE(symbolTable.exists("THAT"));
}

TEST(SymbolTableTest, ShouldAddSymbols){
    SymbolTable symbolTable;

    symbolTable.add("a", 1);
    symbolTable.add("b", 2);
    symbolTable.add("c", 3);

    EXPECT_EQ(symbolTable.get("a"), 1);
    EXPECT_EQ(symbolTable.get("b"), 2);
    EXPECT_EQ(symbolTable.get("c"), 3);
}

TEST(SymbolTableTest, ShouldUpdateSymbols){
    SymbolTable symbolTable;

    symbolTable.add("a", 1);

    EXPECT_EQ(symbolTable.get("a"), 1);

    symbolTable.update("a", 2);

    EXPECT_EQ(symbolTable.get("a"), 2);
}

TEST(SymbolTableTest, ShouldThrowExceptionIfAddIsCalledWhenSymbolAlreadyExists){
    SymbolTable symbolTable;
    symbolTable.add("a", 1);

    try{
        symbolTable.add("a", 2);
        FAIL() << "Expected std::invalid_argument";
    } catch(std::invalid_argument const & error){
        // pass
    }
}

TEST(SymbolTableTest, ShouldThrowExceptionIfUpdateIsCalledWhenSymbolIsNotPresent){
    SymbolTable symbolTable;

    try{
        symbolTable.update("a", 2);
        FAIL() << "Expected std::invalid_argument";
    } catch(std::invalid_argument const & error){
    // pass
    }
}

TEST(SymbolTableTest, ShouldReturnMinusOneIfSymbolIsNotPresentOnGetCall){
    SymbolTable symbolTable;

    EXPECT_EQ(symbolTable.get("a"), -1);
}
