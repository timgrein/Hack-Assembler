#include <string>
#include "CInstruction.h"

#ifndef HACK_ASSEMBLER_CODE_H
#define HACK_ASSEMBLER_CODE_H


class Code {
public:
    std::string translateAInstruction(const std::string &instruction);

    std::string translateCInstruction(const CInstruction &instruction);

    std::string translateJump(const std::string &jump);

    std::string translateDest(const std::string &dest);

    std::string translateComp(const std::string &comp);
};


#endif //HACK_ASSEMBLER_CODE_H
