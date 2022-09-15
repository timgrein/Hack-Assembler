#include "Parser.h"
#include "Utils.h"

#include "SymbolTable.h"

bool Parser::isAInstruction(std::string instruction) {
    instruction = Utils::removeWhitespace(instruction);
    return '@' == instruction.at(0);
}

CInstruction Parser::parseCInstruction(std::string cInstruction) {
    cInstruction = Utils::removeComment(cInstruction);
    cInstruction = Utils::removeWhitespace(cInstruction);

    bool containsEqualsSign = cInstruction.find("=") != std::string::npos;
    bool containsSemicolon = cInstruction.find(";") != std::string::npos;;

    if (containsEqualsSign && containsSemicolon) {
        std::vector <std::string> destAndRest = Utils::split(cInstruction, '=');
        std::vector <std::string> compAndJump = Utils::split(destAndRest[1], ';');

        std::string dest = destAndRest[0];
        std::string comp = compAndJump[0];
        std::string jump = compAndJump[1];

        return {dest, comp, jump};
    }

    if (containsEqualsSign) {
        std::vector <std::string> destAndComp = Utils::split(cInstruction, '=');

        std::string dest = destAndComp[0];
        std::string comp = destAndComp[1];

        return {dest, comp, ""};
    }

    if (containsSemicolon) {
        std::vector <std::string> compAndJump = Utils::split(cInstruction, ';');

        std::string comp = compAndJump[0];
        std::string jump = compAndJump[1];

        return {"", comp, jump};
    }


    return {"", "", ""};
}

bool Parser::isComment(std::string line) {
    line = Utils::removeWhitespace(line);
    return '/' == line.at(0) && '/' == line.at(1);
}

bool Parser::isEmptyLine(const std::string &line) {
    return line.find_first_not_of(" \n\r\t") == std::string::npos;
}

bool Parser::isLabelSymbol(std::string line) {
    line = Utils::removeWhitespace(line);
    line = Utils::removeComment(line);

    return '(' == line.at(0) && ')' == line.at(line.size() - 1);
}

std::string Parser::parseLabelSymbol(std::string line){
    line = Utils::removeWhitespace(line);
    line = Utils::removeComment(line);

    return line.substr(1, line.size() - 2);
}

bool Parser::isPredefinedSymbol(std::string line) {
    return std::find(SymbolTable::predefinedSymbols.begin(), SymbolTable::predefinedSymbols.end(), line) !=
           SymbolTable::predefinedSymbols.end();
}

std::string Parser::parseAInstruction(std::string instruction) {
    instruction = Utils::removeComment(instruction);
    instruction = Utils::removeWhitespace(instruction);

    // remove @ sign
    return instruction.substr(1, instruction.length());
}
