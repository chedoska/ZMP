#include <iostream>
#include <dlfcn.h>
#include <cassert>

#include "AbstractInterp4Command.hh"
#include "ProgramInterpreter.hh"
#include "xmlParser.hh"
#include "Vector3D.hh"

using namespace std;

int main()
{
  Vector3D vec, df;
  vec[0] = 13;
  df[0] = 12;
  df[1] = 5;
  vec = vec + df;
  std::cout << vec << "\n";


  Configuration Config;
   if (!ReadFile("config/config.xml",Config)) return 1;


    std::cout << "LISTA BIBLIOTEK:\n";
    std::list<std::string> lista = Config.getLibsNamesList();
    for(std::string name : lista) std::cout << name << "\n";


  ProgramInterpreter programInterpreter;
  if(!programInterpreter.ExecProgram("/home/chedoska/Pulpit/opis_dzialan.cmd")){
    std::cout << "BŁĄD: Koniec programu!\n\n\n";
  }
  else{
    std::cout << "Program zadziałał poprawnie!\n\n\n";
  }

  return 1;
}

