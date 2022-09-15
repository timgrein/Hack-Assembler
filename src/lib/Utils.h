#ifndef HACK_ASSEMBLER_UTILS_H
#define HACK_ASSEMBLER_UTILS_H

#include <string>
#include <vector>

class Utils {
public:
    static std::vector <std::string> split(const std::string &s, char delim);

    static std::string removeWhitespace(std::string str);

    static std::string removeComment(std::string str);

    static bool isInt(std::string str);

    static bool endsWith(const std::string &string, const std::string &ending);
};


#endif //HACK_ASSEMBLER_UTILS_H
