#ifndef HACK_ASSEMBLER_SYMBOLTABLE_H
#define HACK_ASSEMBLER_SYMBOLTABLE_H

#include <unordered_map>
#include <string>
#include <vector>

class SymbolTable {
public:
    SymbolTable();

    static inline const std::vector<std::string> predefinedSymbols {
        "R0", "R1", "R2", "R3",
        "R4", "R5", "R6", "R7",
        "R8", "R9", "R10", "R11",
        "R12", "R13", "R14", "R15",
        "SCREEN", "KBD",
        "SP", "LCL", "ARG", "THIS", "THAT"} ;

    void add(std::string key, int lineNumber);

    void update(std::string key, int lineNumber);

    int get(std::string key);

    bool exists(const std::string &key);

private:
    std::unordered_map<std::string, int> symbolToRegisterAddress;
};


#endif //HACK_ASSEMBLER_SYMBOLTABLE_H
