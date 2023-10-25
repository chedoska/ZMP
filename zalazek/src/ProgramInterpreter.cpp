#include "ProgramInterpreter.hh"
#include "Preprocessor.hh"

#include <memory>
#include <vector>

ProgramInterpreter::ProgramInterpreter()
{
  std::vector<std::string> DLibNames = {
    "libInterp4Move.so", 
    "libInterp4Set.so",
    "libInterp4Rotate.so", 
    "libInterp4Pause.so"
  };
  for(std::string DLibName : DLibNames){
    std::shared_ptr<LibInterface> libInterface(new LibInterface(DLibName));
    if(libInterface->IsOpen())
      Set4LibInterfaces[libInterface->GetCmdName()] = libInterface;
  }
}

bool ProgramInterpreter::ExecProgram(const char* fileName)
{
  std::fstream cmdFile(fileName);
  std::stringstream textStream;
  textStream << cmdFile.rdbuf();
  textStream = Preprocessor::RunPreprocessor(textStream);

  std::cout << textStream.str();

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
      else
        std::cout << "Błedne parametry do polecenia: "
         << " [" << LineStream.str() << " ]" << "\n\n";
    }
  }
  return true;
}
