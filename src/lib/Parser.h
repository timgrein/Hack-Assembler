#ifndef HACK_ASSEMBLER_PARSER_H
#define HACK_ASSEMBLER_PARSER_H

#include <string>
#include "CInstruction.h"

class Parser {
public:
    Parser() {}

    bool isAInstruction(std::string line);

    bool isComment(std::string line);

    bool isEmptyLine(const std::string &line);

    bool isLabelSymbol(std::string line);

    bool isPredefinedSymbol(std::string line);

    CInstruction parseCInstruction(std::string line);

    std::string parseAInstruction(std::string line);

    std::string parseLabelSymbol(std::string line);
};


#endif //HACK_ASSEMBLER_PARSER_H
