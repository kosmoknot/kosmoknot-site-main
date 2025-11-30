#pragma once
#include <string>
#include <regex>

class ShortHandParser
{
public:
    ShortHandParser();
    std::string Parse(const std::string &iLine);
};
