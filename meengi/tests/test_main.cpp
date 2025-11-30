#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <vector>

#include "GeneratorConfig.h"
#include "LayoutParser.h"
#include "TemplateParser.h"
#include "ShortHandParser.h"
#include "FileHelpers.h"
#include "PageRenderer.h"

namespace
{
namespace fs = std::filesystem;

struct TestFailure : public std::runtime_error
{
    using std::runtime_error::runtime_error;
};

void Expect(bool condition, const std::string &message)
{
    if (!condition)
    {
        throw TestFailure(message);
    }
}

fs::path FixtureRoot()
{
    return fs::path("./tests/fixtures/basic");
}

GeneratorConfig BuildFixtureConfig()
{
    auto root = FixtureRoot();
    GeneratorConfig config;
    config.contentDir = (root / "content").string();
    config.outputDir = (root / "site").string();
    config.layoutPath = (root / "content" / "directives" / "layout.md").string();
    config.templatesPath = (root / "content" / "directives" / "templates.md").string();
    config.warningsFile = (root / "warnings.txt").string();
    return config;
}

void PrepareGenerator()
{
    LayoutParser::Reset();
    PageRenderer::Reset();
    SetGeneratorConfig(BuildFixtureConfig());
}

std::string ReadFile(const fs::path &path)
{
    std::ifstream stream(path);
    Expect(stream.good(), "Failed to open file: " + path.string());
    std::ostringstream buffer;
    buffer << stream.rdbuf();
    return buffer.str();
}

void TestLayoutParserBuildsTree()
{
    PrepareGenerator();
    Node *root = LayoutParser::GetStartNode();
    Expect(root != nullptr, "LayoutParser returned null start node");
    Expect(root->name == "index", "Expected 'index' as root but got '" + root->name + "'");
    Expect(root->children.size() == 2, "index should have two children");
    Node *about = LayoutParser::FindNode("about");
    Expect(about != nullptr, "About node missing");
    Expect(about->parent == root, "About parent mismatch");
}

void TestTemplateParserRendersSimplePage()
{
    TemplateParser parser(BuildFixtureConfig().templatesPath);
    auto output = parser.Parse("$SimplePage(Title,Body)$");
    Expect(output.find("<h1>Title</h1>") != std::string::npos, "TemplateParser failed to render heading");
    Expect(output.find("<p>Body</p>") != std::string::npos, "TemplateParser failed to render body");
}

void TestShortHandParserFormatting()
{
    ShortHandParser parser;
    Expect(parser.Parse("**bold**") == "<b>bold</b>", "Bold conversion failed");
    Expect(parser.Parse("*italic*") == "<i>italic</i>", "Italic conversion failed");
    Expect(parser.Parse("# title") == "<h1>title</h1>", "Heading conversion failed");
    Expect(parser.Parse("```code```") == "<pre>code</pre>", "Code block conversion failed");
    Expect(parser.Parse("/nl") == "<br><br>", "Line break conversion failed");
    Expect(parser.Parse("/hline") == "<div class=\" hrcls\"><hr></ div>", "Horizontal rule conversion failed");
}

void TestFileHelpersUtilities()
{
    auto extracted = ExtractBetween("##Sample", "##", "\n");
    Expect(extracted == "Sample", "ExtractBetween returned '" + extracted + "'");

    auto tokens = TokenizeBetween("$Example(one,two,three)$", ",()");
    Expect(tokens.size() == 3, "TokenizeBetween expected three tokens but received " + std::to_string(tokens.size()));

    int parsed = 0;
    Expect(toInt("42", parsed) && parsed == 42, "toInt failed for valid input");

    std::string templateName;
    std::vector<std::string> args;
    ReadTemplateTitle("# $Simple(a,b,c)", templateName, args);
    Expect(templateName == "Simple", "ReadTemplateTitle wrong name");
    Expect(args.size() == 3, "ReadTemplateTitle wrong arg count");

    std::vector<int> order;
    std::vector<std::string> slices;
    ReadTemplateText("Hello $$a$$ and $$b$$", args, order, slices);
    Expect(order.size() == 2, "ReadTemplateText arg order incorrect");
    Expect(slices.size() == 3, "ReadTemplateText slices incorrect");
}

void TestWarnAndClearRespectConfig()
{
    PrepareGenerator();
    ClearPreviousWarnings();
    warn("example warning");
    auto warningPath = fs::path(BuildFixtureConfig().warningsFile);
    auto content = ReadFile(warningPath);
    Expect(content.find("example warning") != std::string::npos, "Warning not written to configured file");
}

void TestClearPreviousFilesRemovesHtml()
{
    PrepareGenerator();
    auto siteDir = fs::path(BuildFixtureConfig().outputDir);
    fs::create_directories(siteDir);
    auto htmlPath = siteDir / "temp.html";
    auto otherPath = siteDir / "keep.txt";
    {
        std::ofstream(htmlPath) << "temp";
        std::ofstream(otherPath) << "keep";
    }
    ClearPreviousFiles();
    Expect(!fs::exists(htmlPath), "ClearPreviousFiles should remove html files");
    Expect(fs::exists(otherPath), "ClearPreviousFiles should not remove non-html files");
}

void TestPageRendererProducesOutput()
{
    PrepareGenerator();
    ClearPreviousFiles();
    auto start = LayoutParser::GetStartNode();
    PageRenderer::Render(start);
    auto siteDir = fs::path(BuildFixtureConfig().outputDir);
    auto indexPath = siteDir / "index.html";
    auto aboutPath = siteDir / "about.html";
    Expect(fs::exists(indexPath), "index.html was not generated");
    Expect(fs::exists(aboutPath), "about.html was not generated");
    auto indexContent = ReadFile(indexPath);
    Expect(indexContent.find("fixture home page") != std::string::npos, "Rendered index missing body content");
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
        {"LayoutParser builds trees from configured layout", TestLayoutParserBuildsTree},
        {"TemplateParser renders declared templates", TestTemplateParserRendersSimplePage},
        {"ShortHandParser expands markdown shorthands", TestShortHandParserFormatting},
        {"FileHelpers utilities cover template helpers", TestFileHelpersUtilities},
        {"warn() and ClearPreviousWarnings respect config", TestWarnAndClearRespectConfig},
        {"ClearPreviousFiles removes only HTML files", TestClearPreviousFilesRemovesHtml},
        {"PageRenderer renders fixtures into output", TestPageRendererProducesOutput}};

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
