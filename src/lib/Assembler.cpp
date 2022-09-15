#include "Assembler.h"

#include "Utils.h"

std::vector <std::string> Assembler::assemble(const std::vector <std::string> &rawProgram) {
    //first pass
    std::vector <std::string> programWithResolvedLabelSymbols = resolveLabelSymbols(rawProgram);

    //second pass
    std::vector <std::string> assembledProgram = translateToBinary(programWithResolvedLabelSymbols);

    return assembledProgram;
}

std::vector <std::string> Assembler::resolveLabelSymbols(const std::vector <std::string> &rawProgram) {
    std::vector <std::string> programWithResolvedSymbols;

    int lineCount = 0;

    for (int line = 0; line < rawProgram.size(); line++) {
        std::string currentLine = rawProgram.at(line);

        if (parser.isEmptyLine(currentLine) ||
            parser.isComment(currentLine)) {
            continue;
        }

        if (parser.isLabelSymbol(currentLine)) {
            const std::string &parsedLabelSymbol = parser.parseLabelSymbol(currentLine);

            if (!symbolTable.exists(parsedLabelSymbol)) {
                symbolTable.add(parsedLabelSymbol, lineCount);
            }
        } else {
            if (parser.isAInstruction(currentLine) && !parser.isPredefinedSymbol(currentLine)) {
                const std::string aInstruction = parser.parseAInstruction(currentLine);
                if (symbolTable.exists(aInstruction)) {
                    programWithResolvedSymbols.push_back("@" + std::to_string(symbolTable.get(aInstruction)));
                } else {
                    programWithResolvedSymbols.push_back(currentLine);
                }
            } else {
                programWithResolvedSymbols.push_back(currentLine);
            }
            lineCount++;
        }

    }

    return programWithResolvedSymbols;
}

std::vector <std::string> Assembler::translateToBinary(const std::vector <std::string> &programWithResolvedSymbols) {
    std::vector <std::string> translatedProgram;

    int registerAddress = 16;

    for (const std::string &line : programWithResolvedSymbols) {
        if (parser.isAInstruction(line)) {
            const std::string &parsedAInstruction = parser.parseAInstruction(line);
            if (parser.isPredefinedSymbol(parsedAInstruction)) {
                const std::string &predefinedSymbol = parser.parseAInstruction(line);
                int memoryAddressPredefinedSymbol = symbolTable.get(predefinedSymbol);

                translatedProgram.push_back(
                        code.translateAInstruction("@" + std::to_string(memoryAddressPredefinedSymbol)));
            } else if (!Utils::isInt(parsedAInstruction)) {
                if (!symbolTable.exists(parsedAInstruction)) {
                    symbolTable.add(parsedAInstruction, registerAddress);
                    registerAddress++;
                }

                translatedProgram.push_back(
                        code.translateAInstruction("@" + std::to_string(symbolTable.get(parsedAInstruction))));
            } else {
                translatedProgram.push_back(code.translateAInstruction("@" + parsedAInstruction));
            }
        } else {
            CInstruction cInstruction = parser.parseCInstruction(line);
            translatedProgram.push_back(code.translateCInstruction(cInstruction));
        }
    }

    return translatedProgram;
}
