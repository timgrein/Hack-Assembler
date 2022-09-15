#include "FileUtils.h"
#include <fstream>

std::vector <std::string> FileUtils::readInFile(const std::string &path) {
    std::vector <std::string> content;
    std::ifstream fileInputStream(path.c_str());

    if (!fileInputStream) {
        throw std::invalid_argument("File at path " + path + " could not be opened");
    }

    std::string str;
    while (std::getline(fileInputStream, str)) {
        if (str.size() > 0)
            content.push_back(str);
    }

    fileInputStream.close();

    return content;
}

void FileUtils::writeToFile(std::vector <std::string> content, std::string path) {
    std::ofstream outFile(path);
    for (const auto &line : content) outFile << line << "\n";
}
