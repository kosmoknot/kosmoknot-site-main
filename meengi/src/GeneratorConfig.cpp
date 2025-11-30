#include "GeneratorConfig.h"

namespace
{
GeneratorConfig &MutableConfig()
{
    static GeneratorConfig config;
    return config;
}
} // namespace

const GeneratorConfig &GetGeneratorConfig()
{
    return MutableConfig();
}

void SetGeneratorConfig(const GeneratorConfig &config)
{
    MutableConfig() = config;
}
