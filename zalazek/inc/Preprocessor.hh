#pragma once

#include <string>
#include <sstream>

namespace Preprocessor{
    void RemoveComments(std::string& text);
    std::stringstream RunPreprocessor(std::stringstream& cmdListStream);
    int DefineReplace(std::string& text, std::string macroName, int i);
    void RemoveEmptyLines(std::string& text);

    int DefineReplaceArgs(std::string& text, std::string macroName, int i);
}