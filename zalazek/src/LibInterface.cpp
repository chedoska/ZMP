#include "LibInterface.hh"
#include <iostream>
#include <dlfcn.h>
#include <cassert>

LibInterface::LibInterface(const std::string& libName)
    :_Opened(false), _CmdName("")
{
    LibHandler = dlopen(libName.c_str(), RTLD_LAZY);

    if (!LibHandler) {
        std::cerr << "!!! Brak biblioteki: " << libName << std::endl;
        return;
    }

    void *pFun = dlsym(LibHandler,"CreateCmd");
    if (!pFun) {
        std::cerr << "!!! Nie znaleziono funkcji CreateCmd" << std::endl;
        return;
    }
    pCreateCmd = reinterpret_cast<AbstractInterp4Command* (*)(void)>(pFun);

    void *pFun2 = dlsym(LibHandler,"GetCmdName");
    if (!pFun) {
        std::cerr << "!!! Nie znaleziono funkcji GetCmdName" << std::endl;
        return;
    }
    const char*(*pGetCmdName)(void) = *reinterpret_cast<const char* (**)(void)>(&pFun2);
    _CmdName = pGetCmdName();
    _Opened = true;
}

LibInterface::~LibInterface()
{
    if(LibHandler)
        dlclose(LibHandler);
}

std::string LibInterface::GetCmdName() { return _CmdName; }

bool LibInterface::IsOpen() { return _Opened; }
