#include <iostream>
#include <dlfcn.h>
#include <cassert>

#include "AbstractInterp4Command.hh"
#include "ProgramInterpreter.hh"

using namespace std;

int main(int argc, char **argv)
{
  ProgramInterpreter programInterpreter;

  //path =  /home/schedosk/Pulpit/opis_dzialan.cmd
  //path =  config/config.xml

  if(argc < 3)
  {
    std::cout << "Brak śćieżek plików .cmd i .xml\n\n\n";
    return 1;
  }

  if(!programInterpreter.Read_XML_Config(argv[2])){
    std::cout << "BŁĄD czytania pliku XML: Koniec programu!\n\n\n";
    return 1;
  }

  if(!programInterpreter.ExecProgram(argv[1])){
    std::cout << "BŁĄD wykonywania poleceń: Koniec programu!\n\n\n";
  }
  else{
    std::cout << "Program zadziałał poprawnie!\n\n\n";
  }

  return 1;
}

