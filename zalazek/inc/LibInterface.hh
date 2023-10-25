#pragma once

#include "AbstractInterp4Command.hh"

class LibInterface
{
public:
    void *LibHandler;
    std::string GetCmdName();
    AbstractInterp4Command *(*pCreateCmd)(void);
    bool IsOpen();

    LibInterface(const std::string& libFile);
    ~LibInterface();

private:
    std::string _CmdName;
    bool _Opened;
};
