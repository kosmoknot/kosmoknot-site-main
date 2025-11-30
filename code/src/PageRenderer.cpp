#include <queue>
#include <vector>
#include <stdio.h>
#include "PageRenderer.h"
#include "FileHelpers.h"
#include "ShortHandParser.h"

using namespace std;

TemplateParser PageRenderer::templateParser = TemplateParser();
ShortHandParser PageRenderer::shortHandParser = ShortHandParser();
Node *PageRenderer::currentNode = nullptr;

string PageRenderer::GetInputPath(Node *node) { return "./content/" + node->name + ".md"; }

string PageRenderer::GetOutputPath(Node *node) { return "./site/" + node->name + ".html"; }

Node *PageRenderer::GetCurrent() { return currentNode; }

std::string PageRenderer::InterpretLine(const std::string &iLine)
{
    // We might want to change the newline character to <br> instead
    // Or we can put a optional parameter in template.md if need arises
    // Same thing happens at TemplateParser::TemplateParser()
    return shortHandParser.Parse(templateParser.Parse(iLine)) + "\n";
}

void PageRenderer::Render(Node *startNode)
{

    ofstream output;
    queue<Node *> q;
    q.push(startNode);

    while (!q.empty())
    {
        Node *cur = q.front();
        PageRenderer::currentNode = cur;
        q.pop();
        auto children = cur->children;
        if (children.size() != 0)
        {
            for (auto child : children)
                q.push(child);
        }

        output.open(GetOutputPath(cur), ios::app);
        if (output.is_open())
        {
            auto inputLines = GetLinesFromFile(GetInputPath(cur));

            if (inputLines.size() > 0 && output.is_open())
            {
                for (auto line : inputLines)
                {
                    output << InterpretLine(line);
                }
            }
            output.close();
        }
    }
}
