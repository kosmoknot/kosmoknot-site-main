#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "GeneratorConfig.h"
#include "LayoutParser.h"
#include "PageRenderer.h"
#include "FileHelpers.h"

namespace
{
namespace fs = std::filesystem;

struct CLIOptions
{
    std::string contentRoot;
    bool contentProvided = false;
    std::string layoutPath;
    bool layoutProvided = false;
    std::string templatesPath;
    bool templatesProvided = false;
    std::string outputDir;
    bool outputProvided = false;
    std::string warningsFile;
    bool warningsProvided = false;
    bool showHelp = false;
};

fs::path ToAbsolute(const std::string &value, const fs::path &base)
{
    fs::path candidate(value);
    if (candidate.is_absolute())
        return candidate;
    return base / candidate;
}

fs::path ResolveDefaultContent(const fs::path &cwd)
{
    std::vector<fs::path> candidates = {cwd / "content"};
    if (!cwd.parent_path().empty())
        candidates.push_back(cwd.parent_path() / "content");

    std::error_code ec;
    for (const auto &candidate : candidates)
    {
        if (fs::exists(candidate, ec) && fs::is_directory(candidate, ec))
            return fs::weakly_canonical(candidate, ec);
    }
    return fs::weakly_canonical(candidates.front(), ec);
}

void PrintUsage(const char *exe)
{
    std::cout << "Usage: " << exe << " [options]\n\n"
              << "Options:\n"
              << "  --content-root <path>    Directory containing markdown content (default ./content, fallback ../content)\n"
              << "  --layout <file>          Path to layout directives (default <content>/directives/layout.md)\n"
              << "  --templates <file>       Path to template directives (default <content>/directives/templates.md)\n"
              << "  --output-dir <path>      Directory for generated HTML (default sibling 'site' next to content)\n"
              << "  --warnings-file <file>   File to collect warnings (default warnings.txt beside content)\n"
              << "  -h, --help               Show this help text\n";
}

bool ParseArguments(int argc, char **argv, CLIOptions &options, std::string &error)
{
    for (int i = 1; i < argc; ++i)
    {
        std::string arg(argv[i]);
        if (arg == "--content-root" && i + 1 < argc)
        {
            options.contentRoot = argv[++i];
            options.contentProvided = true;
        }
        else if (arg == "--layout" && i + 1 < argc)
        {
            options.layoutPath = argv[++i];
            options.layoutProvided = true;
        }
        else if (arg == "--templates" && i + 1 < argc)
        {
            options.templatesPath = argv[++i];
            options.templatesProvided = true;
        }
        else if (arg == "--output-dir" && i + 1 < argc)
        {
            options.outputDir = argv[++i];
            options.outputProvided = true;
        }
        else if (arg == "--warnings-file" && i + 1 < argc)
        {
            options.warningsFile = argv[++i];
            options.warningsProvided = true;
        }
        else if (arg == "--help" || arg == "-h")
        {
            options.showHelp = true;
        }
        else
        {
            error = "Unknown or incomplete argument: " + arg;
            return false;
        }
    }
    return true;
}

GeneratorConfig BuildConfig(const CLIOptions &options, const fs::path &cwd)
{
    CLIOptions opts = options;

    fs::path contentPath = opts.contentProvided ? ToAbsolute(opts.contentRoot, cwd) : ResolveDefaultContent(cwd);
    fs::path workspaceRoot = contentPath.parent_path();

    if (!opts.layoutProvided)
        opts.layoutPath = (contentPath / "directives" / "layout.md").string();

    if (!opts.templatesProvided)
        opts.templatesPath = (contentPath / "directives" / "templates.md").string();

    GeneratorConfig config;
    config.contentDir = contentPath.string();
    config.layoutPath = ToAbsolute(opts.layoutPath, cwd).string();
    config.templatesPath = ToAbsolute(opts.templatesPath, cwd).string();

    if (opts.outputProvided)
        config.outputDir = ToAbsolute(opts.outputDir, cwd).string();
    else
        config.outputDir = (workspaceRoot.empty() ? fs::path("site") : workspaceRoot / "site").string();

    if (opts.warningsProvided)
        config.warningsFile = ToAbsolute(opts.warningsFile, cwd).string();
    else
        config.warningsFile = (workspaceRoot.empty() ? fs::path("warnings.txt") : workspaceRoot / "warnings.txt").string();

    return config;
}
}

int main(int argc, char **argv)
{
    CLIOptions options;
    std::string error;
    if (!ParseArguments(argc, argv, options, error))
    {
        std::cerr << error << std::endl;
        PrintUsage(argv[0]);
        return 1;
    }

    if (options.showHelp)
    {
        PrintUsage(argv[0]);
        return 0;
    }

    auto config = BuildConfig(options, fs::current_path());
    LayoutParser::Reset();
    PageRenderer::Reset();
    SetGeneratorConfig(config);

    ClearPreviousFiles();

    auto start = LayoutParser::GetStartNode();
    if (start == nullptr)
    {
        std::cerr << "Failed to parse layout. Check " << config.layoutPath << std::endl;
        return 1;
    }

    PageRenderer::Render(start);
    return 0;
}
