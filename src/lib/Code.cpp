#include "Code.h"
#include "bitset"

std::string Code::translateAInstruction(const std::string &aInstruction) {
    std::string instructionWithOutAtSign = aInstruction.substr(1, aInstruction.length());
    int instructionIntValue = std::stoi(instructionWithOutAtSign);

    if (instructionIntValue > 32767) {
        throw std::invalid_argument("Input number has to be a 15 bit number. Max decimal value: 32767");
    }

    return std::bitset<16>(instructionIntValue).to_string();
}

std::string Code::translateCInstruction(const CInstruction &cInstruction) {
    std::string translatedComp = translateComp(cInstruction.comp);
    std::string translatedDest = translateDest(cInstruction.dest);
    std::string translatedJump = translateJump(cInstruction.jump);

    return "111" + translatedComp + translatedDest + translatedJump;
}

std::string Code::translateJump(const std::string &jump) {
    if ("" == jump) {
        return "000";
    }

    if ("JGT" == jump) {
        return "001";
    }

    if ("JEQ" == jump) {
        return "010";
    }

    if ("JGE" == jump) {
        return "011";
    }

    if ("JLT" == jump) {
        return "100";
    }

    if ("JNE" == jump) {
        return "101";
    }

    if ("JLE" == jump) {
        return "110";
    }

    if ("JMP" == jump) {
        return "111";
    }

    throw std::invalid_argument("Jump \"" + jump + "\" is not a valid jump.");
}

std::string Code::translateDest(const std::string &dest) {
    if ("" == dest) {
        return "000";
    }

    if ("M" == dest) {
        return "001";
    }

    if ("D" == dest) {
        return "010";
    }

    if ("MD" == dest) {
        return "011";
    }

    if ("A" == dest) {
        return "100";
    }

    if ("AM" == dest) {
        return "101";
    }

    if ("AD" == dest) {
        return "110";
    }

    if ("AMD" == dest) {
        return "111";
    }

    throw std::invalid_argument("Dest \"" + dest + "\" is not a valid destination.");
}

std::string Code::translateComp(const std::string &comp) {
    if ("0" == comp) {
        return "0101010";
    }

    if ("1" == comp) {
        return "0111111";
    }

    if ("-1" == comp) {
        return "0111010";
    }

    if ("D" == comp) {
        return "0001100";
    }

    if ("A" == comp) {
        return "0110000";
    }

    if ("!D" == comp) {
        return "0001101";
    }

    if ("!A" == comp) {
        return "0110001";
    }

    if ("-D" == comp) {
        return "0001111";
    }

    if ("-A" == comp) {
        return "0110011";
    }

    if ("D+1" == comp) {
        return "0011111";
    }

    if ("A+1" == comp) {
        return "0110111";
    }

    if ("D-1" == comp) {
        return "0001110";
    }

    if ("A-1" == comp) {
        return "0110010";
    }

    if ("D+A" == comp) {
        return "0000010";
    }

    if ("D-A" == comp) {
        return "0010011";
    }

    if ("A-D" == comp) {
        return "0000111";
    }

    if ("D&A" == comp) {
        return "0000000";
    }

    if ("D|A" == comp) {
        return "0010101";
    }

    if ("M" == comp) {
        return "1110000";
    }

    if ("!M" == comp) {
        return "1110001";
    }

    if ("-M" == comp) {
        return "1110011";
    }

    if ("M+1" == comp) {
        return "1110111";
    }

    if ("M-1" == comp) {
        return "1110010";
    }

    if ("D+M" == comp) {
        return "1000010";
    }

    if ("D-M" == comp) {
        return "1010011";
    }

    if ("M-D" == comp) {
        return "1000111";
    }

    if ("D&M" == comp) {
        return "1000000";
    }

    if ("D|M" == comp) {
        return "1010101";
    }

    throw std::invalid_argument("Comp \"" + comp + "\" is not a valid computation.");
}
