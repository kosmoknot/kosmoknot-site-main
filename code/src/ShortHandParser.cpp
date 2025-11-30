#include "ShortHandParser.h"

ShortHandParser::ShortHandParser() {
};

string ShortHandParser::Parse(const string &iLine)
{
    string modifiedLine = iLine;

    // Replace blockquote (handle blockquote separately)
    modifiedLine = regex_replace(modifiedLine, regex("^>\\s*(.*)$"), "<blockquote>$1</blockquote>");

    // Replace bold and italic (these must be processed separately to handle inner text)
    modifiedLine = regex_replace(modifiedLine, regex("\\*\\*(.*?)\\*\\*"), "<b>$1</b>");
    modifiedLine = regex_replace(modifiedLine, regex("\\*(.*?)\\*"), "<i>$1</i>");

    // Replace headings (this is for # heading style, ensuring it's processed separately)
    modifiedLine = regex_replace(modifiedLine, regex("#\\s*(.*)"), "<h1>$1</h1>");

    // Replace code block (using triple backticks for preformatted text)
    modifiedLine = regex_replace(modifiedLine, regex("```(.*?)```"), "<pre>$1</pre>");

    // Replace list items (starts with a hyphen followed by space)
    // modifiedLine = regex_replace(modifiedLine, regex("-\\s*(.*)"), "<li>$1</li>");

    // Replace // with <br><br>
    modifiedLine = regex_replace(modifiedLine, regex("/nl"), "<br><br>");

    // Replace /hline with <div class="hrcls"><hr></ div>
    modifiedLine = regex_replace(modifiedLine, regex("/hline"), "<div class=\" hrcls\"><hr></ div>");

    return modifiedLine; // Return the modified line with HTML tags
};