#include "ProgramInterpreter.hh"

#include <memory>
#include <vector>
#include <cstdio> 
#include <list>

#define MAX_CHAR_COUNT 1000

ProgramInterpreter::ProgramInterpreter()
{
  comChannel.OpenConnection();
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
  Configuration conf;
  if (!ReadFile(fileName,conf)) return false;

  std::cout << "LISTA BIBLIOTEK:\n";
  std::list<std::string> lista = conf.getLibsNamesList();
  for(std::string name : lista) std::cout << name << " " << name.length() << "\n";

  std::cout << "LISTA CUBE:\n";
  std::list<CubeConfiguration> lista2 = conf.getCubeConfigurationsList();
  for(CubeConfiguration name : lista2) name.printAllParams();

  LoadLibraries(conf);

  return true;
}

void ProgramInterpreter::LoadLibraries(Configuration &conf)
{
  std::list<std::string> DLibNames = conf.getLibsNamesList();
  for(std::string DLibName : DLibNames){
    std::shared_ptr<LibInterface> libInterface(new LibInterface(DLibName));
    if(libInterface->IsOpen())
      Set4LibInterfaces[libInterface->GetCmdName()] = libInterface;
  }
}

void ProgramInterpreter::LoadCubeConfiguration(Configuration &conf)
{
  comChannel.Send("Clear\n");
  std::list<CubeConfiguration> cubeConfList = conf.getCubeConfigurationsList();
  for(CubeConfiguration cubeConf : cubeConfList)
  {
    std::stringstream ss;
    ss << "AddObj Name=" << cubeConf.Name
       << " Shift=" << cubeConf.Shift
       << " Scale=" << cubeConf.Scale
       << " RotXYZ_deg=" << cubeConf.RotXYZ_deg
       << " Trans_m=" << cubeConf.Trans_m
       << " RGB=" << cubeConf.RGB << "\n";
    comChannel.Send(ss.str().c_str());
  }
}