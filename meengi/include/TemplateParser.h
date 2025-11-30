#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <set>

class Node;

// First content salami slice + ArgOrder[0]th argument + second content salami slice + ArgOrder[1]th argument ...
class Template
{
private:
    std::vector<int> ArgsOrder;
    std::vector<std::string> ContentSalami;

public:
    Template();
    Template(const std::vector<int> &argOrder, const std::vector<std::string> &contentSalami);
    std::string Parse(const std::vector<std::string> &inputArgs);
};

class TemplateParser
{
private:
    // used to avoid infinite loops
    static std::set<std::string> currentTemplates;
    std::unordered_map<std::string, Template> TemplateMap;
    std::string ParseTemplate(const std::string &name, const std::vector<std::string> &inputArgs);

    // Special Parsing functions
    std::string ParseChildList(Node *node, std::vector<std::string> args);
    std::string ParseNavigList(Node *node, std::vector<std::string> args);
    std::string PasrseTreeMap(Node *node, std::vector<std::string> args);
    std::string ParseTreeMapLevel(Node *node, int lvl);

public:
    TemplateParser();
    TemplateParser(const std::string &templatesPath);
    std::string Parse(const std::string &iLine);
};
