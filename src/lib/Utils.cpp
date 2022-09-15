#include "Utils.h"

#include <iostream>
#include <sstream>

std::vector <std::string> Utils::split(const std::string &s, char delim) {
    std::vector <std::string> result;
    std::stringstream ss(s);
    std::string item;

    while (std::getline(ss, item, delim)) {
        result.push_back(item);
    }

    return result;
}

std::string Utils::removeWhitespace(std::string str) {
    str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
    return str;
}

std::string Utils::removeComment(std::string str) {
    size_t pos = str.find("//");
    if (pos != std::string::npos) {
        str.erase(pos, str.length());
    }

    return str;
}

bool Utils::isInt(std::string str) {
    for (auto chr: str) {
        if (!isdigit(chr)) {
            return false;
        }
    }

    return true;
}

bool Utils::endsWith(const std::string &string, const std::string &ending) {
    if (string.length() >= ending.length()) {
        return (0 == string.compare(string.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}