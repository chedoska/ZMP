#pragma once

#include <map>
#include <memory>
#include <fstream>
#include <string>
#include <sstream>

#include "LibInterface.hh"
#include "Configuration.hh"
#include "xmlParser.hh"
#include "ComChannel.hh"
#include "Scene.hh"

typedef std::map<std::string,std::shared_ptr<LibInterface>> LibManager;

class ProgramInterpreter
{
public:
    ProgramInterpreter();
    ~ProgramInterpreter();
    bool ExecProgram(const char* fileName);
    bool Read_XML_Config(const char* fileName);

private:
    void LoadLibraries(Configuration &conf);
    void LoadCubeConfiguration(Configuration &conf);

    void Read(std::stringstream& str);

    LibManager Set4LibInterfaces;
    Scene scene;
    ComChannel comChannel;
};