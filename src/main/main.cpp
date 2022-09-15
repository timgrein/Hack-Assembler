#include <iostream>

#include <string>
#include <iostream>

#include "../lib/FileUtils.h"
#include "../lib/Utils.h"
#include "../lib/Assembler.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "You've provided the wrong number of arguments: " + std::to_string(argc - 1) + ". Only 2 allowed."
                  << "\n";
        return 1;
    }

    std::string inputFilePath = argv[1];

    if (!Utils::endsWith(inputFilePath, ".asm")) {
        std::cerr << "You've to specify a file ending with \".asm\" as input file." << "\n";
        return 1;
    }

    std::string outputFilePath = argv[2];

    if (!Utils::endsWith(outputFilePath, ".hack")) {
        std::cerr << "You've to specify a file ending with \".hack\" as output file." << "\n";
        return 1;
    }

    try {
        Assembler assembler;

        std::vector <std::string> rawProgram = FileUtils::readInFile(inputFilePath);
        std::vector <std::string> assembledProgram = assembler.assemble(rawProgram);

        FileUtils::writeToFile(assembledProgram, outputFilePath);
    }
    catch (const std::invalid_argument &e) {
        std::cerr << e.what();
    }

    return 0;
}
