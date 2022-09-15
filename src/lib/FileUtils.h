#ifndef HACK_ASSEMBLER_FILEUTILS_H
#define HACK_ASSEMBLER_FILEUTILS_H


#include <string>
#include <vector>

class FileUtils {
public:
    static std::vector <std::string> readInFile(const std::string &path);

    static void writeToFile(std::vector<std::string> content, std::string path);
};


#endif //HACK_ASSEMBLER_FILEUTILS_H
