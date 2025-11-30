#include "TemplateParser.h"
#include "FileHelpers.h"
#include "PageRenderer.h"
#include "GeneratorConfig.h"

using std::string;
using std::vector;

Template::Template(const vector<int> &argOrder, const vector<string> &contentSalami) : ArgsOrder(argOrder), ContentSalami(contentSalami)
{
}

Template::Template()
{
}

// First content salami slice + ArgOrder[0]th argument + second content salami slice + ArgOrder[1]th argument ...
// If less arguments are passed then rest are assumed to be empty
// If more arguments are passed then extra are ignored
string Template::Parse(const vector<string> &inputArgs)
{
    string ret = ContentSalami[0];

    int n = (Max(ArgsOrder) > inputArgs.size()) ? Max(ArgsOrder) : ArgsOrder.size();
    int i;
    for (i = 0; i < n; i++)
    {
        if (ArgsOrder[i] < (int)inputArgs.size())
            ret += inputArgs[ArgsOrder[i]];
        ret += ContentSalami[i + 1];
    }

    // Less than required arguments were given
    i++;
    while (i < (int)ContentSalami.size())
        ret += ContentSalami[i++];

    return ret;
}

std::set<string> TemplateParser::currentTemplates = std::set<string>();
TemplateParser::TemplateParser() : TemplateParser(GetGeneratorConfig().templatesPath)
{
}

TemplateParser::TemplateParser(const std::string &templatePath)
{
    auto Lines = GetLinesFromFile(templatePath);

    bool foundTemplate = false;
    vector<string> args = vector<string>();

    string title;
    string templateText;

    for (auto line : Lines)
    {
        if (line.find("#") != string::npos)
        {
            if (!foundTemplate)
            {
                ReadTemplateTitle(line, title, args);
                foundTemplate = true;
            }
            else
            {
                // Add template to the template map
                vector<int> argsOrder;
                vector<string> salamiSlices;

                // Remove extra \n added at the end
                ReadTemplateText(templateText.substr(0, templateText.size() - 1), args, argsOrder, salamiSlices);

                TemplateMap[title] = Template(argsOrder, salamiSlices);

                templateText = "";
                foundTemplate = false;
            }
        }
        else if (foundTemplate)
        {
            templateText += line;
            // We might want to change the newline character to <br> instead
            // Or we can put a optional parameter in template.md if need arises
            // Same thing happens at PageRenderer::InterpretLine

            // Need to remove extra \n added at the end
            templateText += "\n";
        }
    }
}

string TemplateParser::ParseTemplate(const string &name, const vector<string> &inputArgs)
{
    string output;

    auto temp = TemplateMap.find(name);

    if (temp != TemplateMap.end())
    {
        output = (temp->second).Parse(inputArgs);
    }
    // System templates to fetch info about current page name.
    else if (name == "PageName")
        output = PageRenderer::GetCurrent()->name;

    // Maintaining list of encountered templates in nested cases
    TemplateParser::currentTemplates.insert(name);
    output = TemplateParser::Parse(output);
    TemplateParser::currentTemplates.erase(name);

    return output;
}

string TemplateParser::Parse(const string &iLine)
{
    auto pos_start = iLine.find("$");
    string ret = iLine;

    if (pos_start != string::npos)
    {
        auto pos_end = iLine.find("$", pos_start + 1);
        if (pos_end != string::npos)
        {
            string temp = iLine.substr(pos_start, pos_end - pos_start);

            string templateName = ExtractBetween(temp, "$", "(");

            // Making sure no infinite loops
            if (TemplateParser::currentTemplates.find(templateName) == TemplateParser::currentTemplates.end())
            {
                vector<string> argsList = TokenizeBetween(temp, ",()");
                string newText = "";
                // Parse the special templates
                if (templateName == "ChildList")
                    newText = ParseChildList(PageRenderer::GetCurrent(), argsList);

                else if (templateName == "NavigList")
                    newText = ParseNavigList(PageRenderer::GetCurrent(), argsList);

                else if (templateName == "TreeMap")
                    newText = PasrseTreeMap(LayoutParser::GetStartNode(), argsList);

                else if (templateName == "TreeMapPartial")
                    newText = PasrseTreeMap(PageRenderer::GetCurrent(), argsList);

                else
                    newText = ParseTemplate(templateName, argsList);

                // Look for more templates in that line
                return TemplateParser::Parse(ret.replace(pos_start, pos_end - pos_start + 1, newText));
            }
            // remove the infinite loops
            else
                ret.replace(pos_start, pos_end - pos_start + 1, "");
        }
    }
    return ret;
}

string TemplateParser::ParseChildList(Node *node, vector<string> args)
{
    auto children = node->children;

    string childList = "";
    for (auto child : children)
        childList += ParseTemplate("ChildListItem", vector<string>{child->name});

    vector<string> templateArgs = vector<string>{childList};
    templateArgs.insert(templateArgs.end(), args.begin(), args.end());

    return ParseTemplate("ChildList", templateArgs);
}

string TemplateParser::ParseNavigList(Node *node, vector<string> args)
{
    auto curParent = node;

    string parentList = "";

    while (curParent != nullptr)
    {
        parentList += ParseTemplate("NavigItem", vector<string>{curParent->name});
        curParent = curParent->parent;
    }

    vector<string> templateArgs = vector<string>{parentList};
    templateArgs.insert(templateArgs.end(), args.begin(), args.end());

    return ParseTemplate("NavigList", templateArgs);
}

string TemplateParser::PasrseTreeMap(Node *node, vector<string> args)
{
    string map = "";

    auto curLevel = node->children;
    for (auto curLevelNode : curLevel)
        map += ParseTreeMapLevel(curLevelNode, 1);

    vector<string> templateArgs = vector<string>{map};
    templateArgs.insert(templateArgs.end(), args.begin(), args.end());

    string ret = ParseTemplate("TreeMap", templateArgs);
    return ret;
}

string TemplateParser::ParseTreeMapLevel(Node *node, int lvl)
{
    string titleTemplateName = "";

    if (lvl == 1)
        titleTemplateName = "TreeMapTitle1";
    else
        titleTemplateName = "TreeMapTitle2";

    string childMap = "";
    for (auto child : node->children)
    {
        childMap += ParseTreeMapLevel(child, lvl + 1);
    }

    string ret = ParseTemplate(titleTemplateName, vector<string>{node->name, childMap});
    return ret;
}
