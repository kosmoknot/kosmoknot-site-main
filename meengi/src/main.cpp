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
struct CLIOptions
{
    std::string contentRoot = "./content";
    std::string layoutPath;
    bool layoutProvided = false;
    std::string templatesPath;
    bool templatesProvided = false;
    std::string outputDir = "./site";
    std::string warningsFile = "warnings.txt";
    bool showHelp = false;
};

std::string DefaultLayoutPath(const std::string &contentRoot)
{
    namespace fs = std::filesystem;
    return (fs::path(contentRoot) / "directives" / "layout.md").string();
}

std::string DefaultTemplatesPath(const std::string &contentRoot)
{
    namespace fs = std::filesystem;
    return (fs::path(contentRoot) / "directives" / "templates.md").string();
}

void PrintUsage(const char *exe)
{
    std::cout << "Usage: " << exe << " [options]\n\n"
              << "Options:\n"
              << "  --content-root <path>    Directory containing markdown content (default ./content)\n"
              << "  --layout <file>          Path to layout directives (default <content>/directives/layout.md)\n"
              << "  --templates <file>       Path to template directives (default <content>/directives/templates.md)\n"
              << "  --output-dir <path>      Directory for generated HTML (default ./site)\n"
              << "  --warnings-file <file>   File to collect warnings (default warnings.txt)\n"
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
        }
        else if (arg == "--warnings-file" && i + 1 < argc)
        {
            options.warningsFile = argv[++i];
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

GeneratorConfig BuildConfig(const CLIOptions &options)
{
    CLIOptions opts = options;
    if (!opts.layoutProvided)
    {
        opts.layoutPath = DefaultLayoutPath(opts.contentRoot);
    }
    if (!opts.templatesProvided)
    {
        opts.templatesPath = DefaultTemplatesPath(opts.contentRoot);
    }

    GeneratorConfig config;
    config.contentDir = opts.contentRoot;
    config.layoutPath = opts.layoutPath;
    config.templatesPath = opts.templatesPath;
    config.outputDir = opts.outputDir;
    config.warningsFile = opts.warningsFile;
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

    auto config = BuildConfig(options);
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
