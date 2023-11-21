#include <iostream>
#include <dlfcn.h>
#include <cassert>

#include "AbstractInterp4Command.hh"
#include "ProgramInterpreter.hh"
#include "xmlParser.hh"
#include "ComChannel.hh"

using namespace std;

int main()
{
  Configuration Config;
   if (!ReadFile("config/config.xml",Config)) return 1;

    std::cout << "LISTA BIBLIOTEK:\n";
    std::list<std::string> lista = Config.getLibsNamesList();
    for(std::string name : lista) std::cout << name << " " << name.length() << "\n";

    std::cout << "LISTA CUBE:\n";
    std::list<CubeConfiguration> lista2 = Config.getCubeConfigurationsList();
    for(CubeConfiguration name : lista2) name.printAllParams();


  ProgramInterpreter programInterpreter(Config);
  if(!programInterpreter.ExecProgram("/home/schedosk/Pulpit/opis_dzialan.cmd")){
    std::cout << "BŁĄD: Koniec programu!\n\n\n";
  }
  else{
    std::cout << "Program zadziałał poprawnie!\n\n\n";
  }

  ComChannel com1;
  com1.OpenConnection();
  
  const char *sConfigCmds =
"Clear\n"
"AddObj Name=Podstawa1 RGB=(200,200,200) Scale=(4,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,20) Trans_m=(-1,3,0)\n";
  
  com1.Send(sConfigCmds);
  com1.Send("Close\n");

  return 1;
}

