#include <iostream>
#include "LayoutParser.h"
#include "PageRenderer.h"
#include "FileHelpers.h"
#include "ShortHandParser.h"

int main()
{
    std::cout << "Starting Meengi" << std::endl;

    ShortHandParser SHP;
    std::cout << SHP.Parse("This is **bold**, *italic*, and a #heading with ```code_block```. \n /nl") << std::endl;

    ClearPreviousFiles();

    auto start = LayoutParser::GetStartNode();

    PageRenderer::Render(start);

    return 0;
}