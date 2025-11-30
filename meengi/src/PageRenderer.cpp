#include <queue>
#include <vector>
#include <stdio.h>
#include <filesystem>
#include "PageRenderer.h"
#include "FileHelpers.h"
#include "ShortHandParser.h"
#include "GeneratorConfig.h"

using namespace std;

TemplateParser PageRenderer::templateParser = TemplateParser();
ShortHandParser PageRenderer::shortHandParser = ShortHandParser();
Node *PageRenderer::currentNode = nullptr;
bool PageRenderer::templatesInitialised = false;

string PageRenderer::GetInputPath(Node *node)
{
    namespace fs = std::filesystem;
    fs::path path = fs::path(GetGeneratorConfig().contentDir) / (node->name + ".md");
    return path.string();
}

string PageRenderer::GetOutputPath(Node *node)
{
    namespace fs = std::filesystem;
    fs::path path = fs::path(GetGeneratorConfig().outputDir) / (node->name + ".html");
    return path.string();
}

Node *PageRenderer::GetCurrent() { return currentNode; }

std::string PageRenderer::InterpretLine(const std::string &iLine)
{
    // We might want to change the newline character to <br> instead
    // Or we can put a optional parameter in template.md if need arises
    // Same thing happens at TemplateParser::TemplateParser()
    return shortHandParser.Parse(templateParser.Parse(iLine)) + "\n";
}

void PageRenderer::EnsureTemplates()
{
    if (!templatesInitialised)
        Configure();
}

void PageRenderer::Configure()
{
    templateParser = TemplateParser(GetGeneratorConfig().templatesPath);
    templatesInitialised = true;
}

void PageRenderer::Reset()
{
    templatesInitialised = false;
    templateParser = TemplateParser();
    currentNode = nullptr;
}

void PageRenderer::Render(Node *startNode)
{
    EnsureTemplates();

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

        auto outputPath = GetOutputPath(cur);
        namespace fs = std::filesystem;
        fs::create_directories(fs::path(outputPath).parent_path());

        output.open(outputPath, ios::app);
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
