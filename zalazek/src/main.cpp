#include <iostream>
#include <dlfcn.h>
#include <cassert>

#include "AbstractInterp4Command.hh"
#include "ProgramInterpreter.hh"

using namespace std;

int main()
{
  ProgramInterpreter programInterpreter;

  if(!programInterpreter.Read_XML_Config("config/config.xml")){
    std::cout << "BŁĄD czytania pliku XML: Koniec programu!\n\n\n";
    return 1;
  }

  if(!programInterpreter.ExecProgram("/home/schedosk/Pulpit/opis_dzialan.cmd")){
    std::cout << "BŁĄD wykonywania poleceń: Koniec programu!\n\n\n";
  }
  else{
    std::cout << "Program zadziałał poprawnie!\n\n\n";
  }

  /*ComChannel com1;
  com1.OpenConnection();
  
  const char *sConfigCmds =
"Clear\n"
"AddObj Name=Podstawa1 RGB=(200,200,200) Scale=(4,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,20) Trans_m=(-1,3,0)\n";
  
  com1.Send(sConfigCmds);
  com1.Send("Close\n");*/

  return 1;
}

