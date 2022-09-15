#include <gtest/gtest.h>
#include "src/lib/Code.h"

TEST(CodeTest, ShouldTranslateAnAInstruction) {
    Code code;

    std::string aInstruction = "@21";
    std::string expectedBinaryOutput = "0000000000010101";

    std::string actualBinaryOutput = code.translateAInstruction(aInstruction);

    EXPECT_EQ(actualBinaryOutput, expectedBinaryOutput);
}

TEST(CodeTest, ShouldThrowExceptionForNumberGreaterThanFifteenBits){
    Code code;
    std::string aInstruction = "@60000";

    try{
        code.translateAInstruction(aInstruction);
        FAIL() << "Expected std::invalid_argument";
    } catch(std::invalid_argument const & error){
        // pass
    }
}

TEST(CodeTest, ShouldThrowExceptionForInvalidJump){
    Code code;

    try{
        code.translateJump("INVALID");
        FAIL() << "Expected std::invalid_argument";
    } catch(std::invalid_argument const & error){
        // pass
    }
}

TEST(CodeTest, ShouldTranslateNullJumpCorrectly){
    Code code;

    std::string nullJump = "";
    std::string nullJumpBinary = code.translateJump(nullJump);

    EXPECT_EQ(nullJumpBinary, "000");
}

TEST(CodeTest, ShouldTranslateJGTCorrectly){
    Code code;

    std::string jgt = "JGT";
    std::string jgtBinary = code.translateJump(jgt);

    EXPECT_EQ(jgtBinary, "001");
}

TEST(CodeTest, ShouldTranslateJEQCorrectly){
    Code code;

    std::string jeq = "JEQ";
    std::string jeqBinary = code.translateJump(jeq);

    EXPECT_EQ(jeqBinary, "010");
}

TEST(CodeTest, ShouldTranslateJGECorrectly){
    Code code;

    std::string jge = "JGE";
    std::string jgeBinary = code.translateJump(jge);

    EXPECT_EQ(jgeBinary, "011");
}

TEST(CodeTest, ShouldTranslateJLTCorrectly){
    Code code;

    std::string jlt = "JLT";
    std::string jltBinary = code.translateJump(jlt);

    EXPECT_EQ(jltBinary, "100");
}

TEST(CodeTest, ShouldTranslateJNECorrectly){
    Code code;

    std::string jne = "JNE";
    std::string jneBinary = code.translateJump(jne);

    EXPECT_EQ(jneBinary, "101");
}

TEST(CodeTest, ShouldTranslateJLECorrectly){
    Code code;

    std::string jle = "JLE";
    std::string jleBinary = code.translateJump(jle);

    EXPECT_EQ(jleBinary, "110");
}

TEST(CodeTest, ShouldTranslateJMPCorrectly){
    Code code;

    std::string jmp = "JMP";
    std::string jmpBinary = code.translateJump(jmp);

    EXPECT_EQ(jmpBinary, "111");
}

TEST(CodeTest, ShouldThrowExceptionForInvalidDest){
    Code code;

    try{
        code.translateDest("INVALID");
        FAIL() << "Expected std::invalid_argument";
    } catch(std::invalid_argument const & error){
        // pass
    }
}

TEST(CodeTest, ShouldTranslateNullDestCorrectly){
    Code code;

    std::string nullDest = "";
    std::string nullDestBinary = code.translateDest(nullDest);

    EXPECT_EQ(nullDestBinary, "000");
}

TEST(CodeTest, ShouldTranslateMDestCorrectly){
    Code code;

    std::string mDest = "M";
    std::string mDestBinary = code.translateDest(mDest);

    EXPECT_EQ(mDestBinary, "001");
}

TEST(CodeTest, ShouldTranslateDDestCorrectly){
    Code code;

    std::string dDest = "D";
    std::string dDestBinary = code.translateDest(dDest);

    EXPECT_EQ(dDestBinary, "010");
}

TEST(CodeTest, ShouldTranslateMDDestCorrectly){
    Code code;

    std::string mdDest = "MD";
    std::string mdDestBinary = code.translateDest(mdDest);

    EXPECT_EQ(mdDestBinary, "011");
}

TEST(CodeTest, ShouldTranslateADestCorrectly){
    Code code;

    std::string aDest = "A";
    std::string aDestBinary = code.translateDest(aDest);

    EXPECT_EQ(aDestBinary, "100");
}

TEST(CodeTest, ShouldTranslateAMDestCorrectly){
    Code code;

    std::string amDest = "AM";
    std::string amDestBinary = code.translateDest(amDest);

    EXPECT_EQ(amDestBinary, "101");
}

TEST(CodeTest, ShouldTranslateADDestCorrectly){
    Code code;

    std::string adDest = "AD";
    std::string adDestBinary = code.translateDest(adDest);

    EXPECT_EQ(adDestBinary, "110");
}

TEST(CodeTest, ShouldTranslateAMDDestCorrectly){
    Code code;

    std::string amdDest = "AMD";
    std::string amdDestBinary = code.translateDest(amdDest);

    EXPECT_EQ(amdDestBinary, "111");
}

TEST(CodeTest, ShouldThrowExceptionForInvalidComp){
    Code code;

    try{
        code.translateComp("INVALID");
        FAIL() << "Expected std::invalid_argument";
    } catch(std::invalid_argument const & error){
        // pass
    }
}

TEST(CodeTest, ShouldTranslateZeroCompCorrectly){
    Code code;

    std::string zeroComp = "0";
    std::string zeroCompBinary = code.translateComp(zeroComp);

    EXPECT_EQ(zeroCompBinary, "0101010");
}

TEST(CodeTest, ShouldTranslateOneCompCorrectly){
    Code code;

    std::string oneComp = "1";
    std::string oneCompBinary = code.translateComp(oneComp);

    EXPECT_EQ(oneCompBinary, "0111111");
}

TEST(CodeTest, ShouldTranslateMinusOneCompCorrectly){
    Code code;

    std::string minusOneComp = "-1";
    std::string minusOneCompBinary = code.translateComp(minusOneComp);

    EXPECT_EQ(minusOneCompBinary, "0111010");
}

TEST(CodeTest, ShouldTranslateDCompCorrectly){
    Code code;

    std::string dComp = "D";
    std::string dCompBinary = code.translateComp(dComp);

    EXPECT_EQ(dCompBinary, "0001100");
}

TEST(CodeTest, ShouldTranslateACompCorrectly){
    Code code;

    std::string aComp = "A";
    std::string aCompBinary = code.translateComp(aComp);

    EXPECT_EQ(aCompBinary, "0110000");
}

TEST(CodeTest, ShouldTranslateNotDCompCorrectly){
    Code code;

    std::string notDComp = "!D";
    std::string notDCompBinary = code.translateComp(notDComp);

    EXPECT_EQ(notDCompBinary, "0001101");
}

TEST(CodeTest, ShouldTranslateNotACompCorrectly){
    Code code;

    std::string notAComp = "!A";
    std::string notACompBinary = code.translateComp(notAComp);

    EXPECT_EQ(notACompBinary, "0110001");
}

TEST(CodeTest, ShouldTranslateMinusDCompCorrectly){
    Code code;

    std::string minusDComp = "-D";
    std::string minusDCompBinary = code.translateComp(minusDComp);

    EXPECT_EQ(minusDCompBinary, "0001111");
}

TEST(CodeTest, ShouldTranslateMinusACompCorrectly){
    Code code;

    std::string minusAComp = "-A";
    std::string minusACompBinary = code.translateComp(minusAComp);

    EXPECT_EQ(minusACompBinary, "0110011");
}

TEST(CodeTest, ShouldTranslateDPlusOneCompCorrectly){
    Code code;

    std::string dPlusOneComp = "D+1";
    std::string dPlusOneCompBinary = code.translateComp(dPlusOneComp);

    EXPECT_EQ(dPlusOneCompBinary, "0011111");
}

TEST(CodeTest, ShouldTranslateAPlusOneCompCorrectly){
    Code code;

    std::string aPlusOneComp = "A+1";
    std::string aPlusOneCompBinary = code.translateComp(aPlusOneComp);

    EXPECT_EQ(aPlusOneCompBinary, "0110111");
}

TEST(CodeTest, ShouldTranslateDMinusOneCompCorrectly){
    Code code;

    std::string dMinusOneComp = "D-1";
    std::string dMinusOneCompBinary = code.translateComp(dMinusOneComp);

    EXPECT_EQ(dMinusOneCompBinary, "0001110");
}

TEST(CodeTest, ShouldTranslateAMinusOneCompCorrectly){
    Code code;

    std::string aMinusOneComp = "A-1";
    std::string aMinusOneCompBinary = code.translateComp(aMinusOneComp);

    EXPECT_EQ(aMinusOneCompBinary, "0110010");
}

TEST(CodeTest, ShouldTranslateDPlusACompCorrectly){
    Code code;

    std::string dPlusAComp = "D+A";
    std::string dPlusACompBinary = code.translateComp(dPlusAComp);

    EXPECT_EQ(dPlusACompBinary, "0000010");
}

TEST(CodeTest, ShouldTranslateDMinusACompCorrectly){
    Code code;

    std::string dMinusAComp = "D-A";
    std::string dMinusACompBinary = code.translateComp(dMinusAComp);

    EXPECT_EQ(dMinusACompBinary, "0010011");
}

TEST(CodeTest, ShouldTranslateAMinusDCompCorrectly){
    Code code;

    std::string aMinusDComp = "A-D";
    std::string aMinusDCompBinary = code.translateComp(aMinusDComp);

    EXPECT_EQ(aMinusDCompBinary, "0000111");
}

TEST(CodeTest, ShouldTranslateDAndACompCorrectly){
    Code code;

    std::string dAndAComp = "D&A";
    std::string dAndACompBinary = code.translateComp(dAndAComp);

    EXPECT_EQ(dAndACompBinary, "0000000");
}

TEST(CodeTest, ShouldTranslateDOrACompCorrectly){
    Code code;

    std::string dOrAComp = "D|A";
    std::string dOrACompBinary = code.translateComp(dOrAComp);

    EXPECT_EQ(dOrACompBinary, "0010101");
}

TEST(CodeTest, ShouldTranslateMCompCorrectly){
    Code code;

    std::string mComp = "M";
    std::string mCompBinary = code.translateComp(mComp);

    EXPECT_EQ(mCompBinary, "1110000");
}

TEST(CodeTest, ShouldTranslateNotMCompCorrectly){
    Code code;

    std::string notMComp = "!M";
    std::string notMCompBinary = code.translateComp(notMComp);

    EXPECT_EQ(notMCompBinary, "1110001");
}

TEST(CodeTest, ShouldTranslateMinusMCompCorrectly){
    Code code;

    std::string minusMComp = "-M";
    std::string minusMCompBinary = code.translateComp(minusMComp);

    EXPECT_EQ(minusMCompBinary, "1110011");
}

TEST(CodeTest, ShouldTranslateMPlusOneCompCorrectly){
    Code code;

    std::string mPlusOneComp = "M+1";
    std::string mPlusOneCompBinary = code.translateComp(mPlusOneComp);

    EXPECT_EQ(mPlusOneCompBinary, "1110111");
}

TEST(CodeTest, ShouldTranslateMMinusOneCompCorrectly){
    Code code;

    std::string mMinusOneComp = "M-1";
    std::string mMinusOneCompBinary = code.translateComp(mMinusOneComp);

    EXPECT_EQ(mMinusOneCompBinary, "1110010");
}

TEST(CodeTest, ShouldTranslateDPlusMCompCorrectly){
    Code code;

    std::string dPlusMComp = "D+M";
    std::string dPlusMCompBinary = code.translateComp(dPlusMComp);

    EXPECT_EQ(dPlusMCompBinary, "1000010");
}

TEST(CodeTest, ShouldTranslateDMinusMCompCorrectly){
    Code code;

    std::string dMinusMComp = "D-M";
    std::string dMinusMCompBinary = code.translateComp(dMinusMComp);

    EXPECT_EQ(dMinusMCompBinary, "1010011");
}

TEST(CodeTest, ShouldTranslateMMinusDCompCorrectly){
    Code code;

    std::string mMinusDComp = "M-D";
    std::string mMinusDCompBinary = code.translateComp(mMinusDComp);

    EXPECT_EQ(mMinusDCompBinary, "1000111");
}

TEST(CodeTest, ShouldTranslateDAndMCompCorrectly){
    Code code;

    std::string dAndMComp = "D&M";
    std::string dAndMCompBinary = code.translateComp(dAndMComp);

    EXPECT_EQ(dAndMCompBinary, "1000000");
}

TEST(CodeTest, ShouldTranslateDOrMCompCorrectly){
    Code code;

    std::string dOrMComp = "D|M";
    std::string dOrMCompBinary = code.translateComp(dOrMComp);

    EXPECT_EQ(dOrMCompBinary, "1010101");
}

TEST(CodeTest, ShouldTranslateCInstructionCorrectly){
    Code code;

    CInstruction cInstruction = {.dest = "D", .comp = "M+1", .jump = "JGT"};
    std::string translatedCInstruction = code.translateCInstruction(cInstruction);

    EXPECT_EQ(translatedCInstruction, "1111110111010001");
}