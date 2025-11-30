#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>

#include "LayoutParser.h"
#include "TemplateParser.h"
#include "ShortHandParser.h"
#include "FileHelpers.h"

namespace
{
void Expect(bool condition, const std::string &message)
{
    if (!condition)
    {
        throw std::runtime_error(message);
    }
}

void TestLayoutParserBasic()
{
    Node *root = LayoutParser::GetStartNode();
    Expect(root != nullptr, "LayoutParser returned a null start node");
    Expect(root->name == "index", "Expected start node to be 'index' but got '" + root->name + "'");

    bool foundLogs = false;
    for (auto child : root->children)
    {
        if (child != nullptr && child->parent != root)
        {
            throw std::runtime_error("Child '" + child->name + "' does not reference the start node as its parent");
        }
        if (child != nullptr && child->name == "Logs")
        {
            foundLogs = true;
        }
    }
    Expect(foundLogs, "Expected to find 'Logs' as a child of 'index' but it was missing");

    Node *logsNode = LayoutParser::FindNode("Logs");
    Expect(logsNode != nullptr, "LayoutParser::FindNode failed to locate the 'Logs' node");
    Expect(logsNode->parent == root, "'Logs' should report 'index' as its parent");
}

void TestTemplateArgumentReplacement()
{
    Template wrapper({0, 1}, {"<div>", " - ", "</div>"});

    auto withTwoArgs = wrapper.Parse(std::vector<std::string>{"left", "right"});
    Expect(withTwoArgs == "<div>left - right</div>", "Template failed to interpolate both arguments in order");

    auto withMissingArg = wrapper.Parse(std::vector<std::string>{"solo"});
    Expect(withMissingArg == "<div>solo - </div>", "Template should treat missing arguments as empty strings");
}

void TestShortHandParserFormatting()
{
    ShortHandParser parser;

    Expect(parser.Parse("**bold**") == "<b>bold</b>", "Bold markup conversion failed");
    Expect(parser.Parse("*italic*") == "<i>italic</i>", "Italic markup conversion failed");
    Expect(parser.Parse("# heading") == "<h1>heading</h1>", "Heading markup conversion failed");
    Expect(parser.Parse("```code```") == "<pre>code</pre>", "Code block conversion failed");
    Expect(parser.Parse("/nl") == "<br><br>", "New line shorthand conversion failed");
    Expect(parser.Parse("/hline") == "<div class=\" hrcls\"><hr></ div>", "Horizontal line shorthand conversion failed");
}

void TestFileHelpersUtilities()
{
    auto extracted = ExtractBetween("##Sample\n", "##", "\n");
    Expect(extracted == "Sample", "ExtractBetween did not return text between tokens");

    auto tokens = TokenizeBetween("$Example(one,two,three)$", ",()");
    Expect(tokens.size() == 3, "TokenizeBetween should return three arguments");
    Expect(tokens[0] == "one" && tokens[1] == "two" && tokens[2] == "three", "TokenizeBetween returned unexpected argument order");
}
} // namespace

int main()
{
    struct TestCase
    {
        const char *name;
        void (*fn)();
    };

    std::vector<TestCase> tests = {
        {"LayoutParser establishes the expected root tree", TestLayoutParserBasic},
        {"Template handles argument substitution and padding", TestTemplateArgumentReplacement},
        {"ShortHandParser expands markdown-like shorthands", TestShortHandParserFormatting},
        {"FileHelpers string utilities behave deterministically", TestFileHelpersUtilities}};

    size_t passed = 0;
    size_t failed = 0;

    for (const auto &test : tests)
    {
        try
        {
            test.fn();
            std::cout << "[PASS] " << test.name << std::endl;
            passed++;
        }
        catch (const std::exception &ex)
        {
            std::cout << "[FAIL] " << test.name << ": " << ex.what() << std::endl;
            failed++;
        }
        catch (...)
        {
            std::cout << "[FAIL] " << test.name << ": Unknown exception" << std::endl;
            failed++;
        }
    }

    std::cout << "Passed " << passed << " of " << tests.size() << " tests." << std::endl;
    if (failed != 0)
    {
        std::cout << failed << " test(s) failed." << std::endl;
        return 1;
    }

    return 0;
}
