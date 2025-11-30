#pragma once
#include <fstream>

#include "LayoutParser.h"
#include "TemplateParser.h"
#include "ShortHandParser.h"

class PageRenderer
{
private:
    static TemplateParser templateParser;
    static ShortHandParser shortHandParser;
    static Node *currentNode;
    static bool templatesInitialised;

    PageRenderer();
    static std::string GetInputPath(Node *node);
    static std::string GetOutputPath(Node *node);
    static std::string InterpretLine(const std::string &iLine);
    static void EnsureTemplates();

public:
    static void Render(Node *startNode);
    static Node *GetCurrent();
    static void Configure();
    static void Reset();
};
