#include <iostream>
#include "LayoutParser.h"
#include "FileHelpers.h"
#include "GeneratorConfig.h"

Node::Node(std::string name, Node *parent) : name(name), parent(parent)
{
    children = std::vector<Node *>();
}

void Node::AddChild(Node *child)
{
    children.push_back(child);
}

Node::Node() : name("Uninitialised"), parent(nullptr)
{
    children = std::vector<Node *>();
}

void Node::Print() const
{
    std::cout << name << " -> { " << std::endl;
    if (children.size() != 0)
    {
        for (auto child : children)
        {
            child->Print();
            std::cout << " , " << std::endl;
        }
    }
    std::cout << " } " << std::endl;
}

// Initialise the static variables
LayoutParser *LayoutParser::instance = nullptr;

LayoutParser *LayoutParser::GetInstance()
{
    if (instance == nullptr)
        instance = new LayoutParser(GetGeneratorConfig().layoutPath);

    return instance;
}

Node *LayoutParser::GetStartNode()
{
    return &LayoutParser::GetInstance()->StartNode;
}

const std::map<std::string, Node *> &LayoutParser::GetMap() const
{
    return NodeMap;
}

Node *LayoutParser::FindNode(const std::string &name)
{
    auto &map = LayoutParser::GetInstance()->GetMap();
    auto search = map.find(name);
    if (search == map.end())
        return nullptr;
    return search->second;
}

void LayoutParser::SaveInMap(Node *node, const std::string str)
{
    if (node == nullptr)
        return;

    NodeMap[str] = node;
}

LayoutParser::LayoutParser(const std::string &path)
{
    auto lines = GetLinesFromFile(path);
    Node *currentParent = nullptr;
    for (auto line : lines)
    {
        bool isParent = false;
        bool isChild = false;

        auto pos = line.find("#");
        if (pos != string::npos)
        {
            if (line[pos + 1] == '#')
            {
                isParent = true;
            }
            else
                isChild = true;
        }
        if (isParent)
        {
            string name = ExtractBetween(line, "##", "\n");
            Node *current = NodeMap[name];

            if (current == nullptr)
            {
                if (StartNode.name == "Uninitialised")
                {
                    StartNode.name = name;
                    StartNode.parent = nullptr;
                    SaveInMap(&StartNode, name);
                    currentParent = &StartNode;
                }
                else
                {
                    // Parent needs to be encountered as a child before unless it is the homeTitle
                    string warning = "In layout, " + name + " is used as PageTitle without listing it first under a PageTitle. Hence ignored";
                    warn(warning);
                }
            }
            else
            {
                currentParent = current;
            }
        }
        else if (isChild)
        {
            string name = ExtractBetween(line, "#", "\n");

            auto current = NodeMap[name];

            if (current == nullptr)
            {
                current = new Node(name);
                SaveInMap(current, name);
            }

            // Child must not have been initiated before to avoid possible circular references
            else
            {
                string warning = "In layout, " + name + " Is listed under multiple PageTitles. Hence ignored after first encounter. Avoid listing single page under multiple pageTitles";
                warn(warning);
            }

            if (currentParent != nullptr)
            {
                current->parent = currentParent;
                currentParent->AddChild(current);
            }
        }
    }
}

LayoutParser::~LayoutParser()
{
    for (auto &entry : NodeMap)
    {
        if (entry.second != &StartNode)
        {
            delete entry.second;
        }
    }
    NodeMap.clear();
}

void LayoutParser::Reset()
{
    if (instance != nullptr)
    {
        delete instance;
        instance = nullptr;
    }
}
