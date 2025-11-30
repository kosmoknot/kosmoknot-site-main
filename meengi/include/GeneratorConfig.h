#pragma once

#include <string>

struct GeneratorConfig
{
    std::string contentDir = "./content";
    std::string outputDir = "./site";
    std::string layoutPath = "./content/directives/layout.md";
    std::string templatesPath = "./content/directives/templates.md";
    std::string warningsFile = "warnings.txt";
};

const GeneratorConfig &GetGeneratorConfig();
void SetGeneratorConfig(const GeneratorConfig &config);
