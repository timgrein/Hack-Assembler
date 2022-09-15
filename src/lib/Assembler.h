#ifndef HACK_ASSEMBLER_ASSEMBLER_H
#define HACK_ASSEMBLER_ASSEMBLER_H

#include <vector>
#include <string>

#include "SymbolTable.h"
#include "Parser.h"
#include "Code.h"

class Assembler {
public:
    std::vector<std::string> assemble(const std::vector<std::string> &rawProgram);

    std::vector<std::string> resolveLabelSymbols(const std::vector<std::string> &rawProgram);

    std::vector<std::string> translateToBinary(const std::vector<std::string> &programWithResolvedSymbols);
private:
    SymbolTable symbolTable;
    Parser parser;
    Code code;
};


#endif //HACK_ASSEMBLER_ASSEMBLER_H
