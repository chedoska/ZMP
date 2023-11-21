#include "ProgramInterpreter.hh"

#include <memory>
#include <vector>
#include <cstdio> 
#include <list>

#define MAX_CHAR_COUNT 1000

ProgramInterpreter::ProgramInterpreter()
{
  std::list<std::string> DLibNames = conf.getLibsNamesList();
  for(std::string DLibName : DLibNames){
    std::shared_ptr<LibInterface> libInterface(new LibInterface(DLibName));
    if(libInterface->IsOpen())
      Set4LibInterfaces[libInterface->GetCmdName()] = libInterface;
  }
}

bool ProgramInterpreter::ExecProgram(const char* fileName)
{
  std::string Cmd4Preproc = "cpp -P ";
  char Line[MAX_CHAR_COUNT];
  std::stringstream textStream;

  Cmd4Preproc += fileName;
  FILE *pProc = popen(Cmd4Preproc.c_str(),"r");

  if(!pProc) return false;

  while(std::fgets(Line, MAX_CHAR_COUNT, pProc)){
    textStream << Line;
  }

  std::cout << "\n" << textStream.str() << "\n";

  std::string LineString;
  while(std::getline(textStream, LineString)){
    std::istringstream LineStream(LineString);
    std::string CmdName;
    LineStream >> CmdName;
    if(Set4LibInterfaces.count(CmdName) != 0){
      AbstractInterp4Command *pCmd = Set4LibInterfaces[CmdName]->pCreateCmd();
      if(pCmd->ReadParams(LineStream)){
        std::cout << "Zinterpretowane polecenie: ";
        pCmd->PrintCmd();
        std::cout << "\n";
      }
      else{
        std::cout << "Błedne parametry do polecenia: "
         << " [\"" << LineStream.str() << "\" ]" << "\n\n";
         return false;
      }
    }
    else{
      std::cout << "Nie znane polecenie: \"" << CmdName << "\"\n\n";
      return false;
    }
  }
  return true;
}

bool ProgramInterpreter::Read_XML_Config(const char* fileName)
{
  if (!ReadFile(fileName,conf)) return false;

  std::cout << "LISTA BIBLIOTEK:\n";
  std::list<std::string> lista = conf.getLibsNamesList();
  for(std::string name : lista) std::cout << name << " " << name.length() << "\n";

  std::cout << "LISTA CUBE:\n";
  std::list<CubeConfiguration> lista2 = conf.getCubeConfigurationsList();
  for(CubeConfiguration name : lista2) name.printAllParams();

  return true;
}