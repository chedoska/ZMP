#pragma once

#include <map>
#include <memory>
#include <fstream>
#include <string>
#include <sstream>

#include "LibInterface.hh"
#include "Configuration.hh"

typedef std::map<std::string,std::shared_ptr<LibInterface>> LibManager;

class ProgramInterpreter
{
public:
    ProgramInterpreter(Configuration& conf);
    bool ExecProgram(const char* fileName);

private:
    LibManager Set4LibInterfaces;
    // Scene...
    // Com...
};