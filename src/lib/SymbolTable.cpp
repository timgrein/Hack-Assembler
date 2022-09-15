
#include "SymbolTable.h"

SymbolTable::SymbolTable() {
    // pre-defined "virtual registers"
    symbolToRegisterAddress["R0"] = 0;
    symbolToRegisterAddress["R1"] = 1;
    symbolToRegisterAddress["R2"] = 2;
    symbolToRegisterAddress["R3"] = 3;
    symbolToRegisterAddress["R4"] = 4;
    symbolToRegisterAddress["R5"] = 5;
    symbolToRegisterAddress["R6"] = 6;
    symbolToRegisterAddress["R7"] = 7;
    symbolToRegisterAddress["R8"] = 8;
    symbolToRegisterAddress["R9"] = 9;
    symbolToRegisterAddress["R10"] = 10;
    symbolToRegisterAddress["R11"] = 11;
    symbolToRegisterAddress["R12"] = 12;
    symbolToRegisterAddress["R13"] = 13;
    symbolToRegisterAddress["R14"] = 14;
    symbolToRegisterAddress["R15"] = 15;

    // memory map locations for screen and keyboard I/O
    symbolToRegisterAddress["SCREEN"] = 16384;
    symbolToRegisterAddress["KBD"] = 24576;

    symbolToRegisterAddress["SP"] = 0;
    symbolToRegisterAddress["LCL"] = 1;
    symbolToRegisterAddress["ARG"] = 2;
    symbolToRegisterAddress["THIS"] = 3;
    symbolToRegisterAddress["THAT"] = 4;
}

void SymbolTable::add(std::string key, int lineNumber) {
    if(exists(key)){
        throw std::invalid_argument("Key " + key + " already present in symbol table. Update the symbol instead");
    }

    symbolToRegisterAddress[key] = lineNumber;
}

bool SymbolTable::exists(const std::string &key) {
    return !(symbolToRegisterAddress.find(key) == symbolToRegisterAddress.end());
}

void SymbolTable::update(std::string key, int lineNumber) {
    if(!exists(key)){
        throw std::invalid_argument("Key " + key + " not present in symbol table. Add the symbol first");
    }

    symbolToRegisterAddress[key] = lineNumber;
}

int SymbolTable::get(std::string key) {
    if(!exists(key)){
        return -1;
    }

    return symbolToRegisterAddress[key];
}