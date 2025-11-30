#pragma once
#include <string>
#include <regex>

using namespace std;

class ShortHandParser
{
public:
    ShortHandParser();
    string Parse(const string &iLine);
};