#pragma once
#include <string>
#include <vector>
#include <fstream>

std::vector<std::string> GetLinesFromFile(const std::string &path, bool ignore_comments = true);
std::string ExtractBetween(const std::string &target, const std::string &start, const std::string &end);
std::string ExtractBetween(const std::string &target, const size_t &p_start, const std::string &end);
std::vector<std::string> TokenizeBetween(const std::string &target, const std::string &tokens);

// writes out warnings to warnings.txt
void warn(const std::string &warning);

// uses try catch block to avoid crashing
bool toInt(const std::string &str, int &out);

void ClearPreviousFiles();
void ClearPreviousWarnings();

void ReadTemplateTitle(const std::string &iLine, std::string &templateName, std::vector<std::string> &argsList);
void ReadTemplateText(const std::string &input, const std::vector<std::string> &argsList, std::vector<int> &argsOrder, std::vector<std::string> &salamiSlices);

std::string Trim(const std::string &input);

/////////////////////
// Not really file helpers but didn't really want to rename the whole file
/////////////////////

// Need this to find out how many arguments do we have in a template
size_t Max(const std::vector<int> &vec);
