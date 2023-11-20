#include <iostream>
#include <dlfcn.h>
#include <cassert>

#include "AbstractInterp4Command.hh"
#include "ProgramInterpreter.hh"
#include "xmlParser.hh"

using namespace std;

int main()
{
  Configuration Config;
   if (!ReadFile("config/config.xml",Config)) return 1;

  ProgramInterpreter programInterpreter;
  if(!programInterpreter.ExecProgram("/home/chedoska/Pulpit/opis_dzialan.cmd")){
    std::cout << "BŁĄD: Koniec programu!\n\n\n";
  }
  else{
    std::cout << "Program zadziałał poprawnie!\n\n\n";
  }

  return 1;
}

