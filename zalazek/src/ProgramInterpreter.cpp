#include "ProgramInterpreter.hh"
#include "MobileObj.hh"

#include <memory>
#include <vector>
#include <cstdio> 
#include <list>

#define MAX_CHAR_COUNT 1000

ProgramInterpreter::ProgramInterpreter()
{
  std::cout << "Łączenie z serwerem\n";
  if(!comChannel.OpenConnection())
  {
    std::cout << "Nie udało się połączyć z serwerem\n";
  }
}

ProgramInterpreter::~ProgramInterpreter()
{
  std::cout << "zamykanie połączenia z serwerem\n";
  comChannel.CloseConnection();
}


void ProgramInterpreter::Read(std::stringstream& str)
{
  std::list<std::thread> currentThreads;
  std::string LineString;
  while(str >> LineString)
  {
    if(LineString == "Begin_Parallel_Actions"){
      std::cout << "Nowy wątek sekcji\n\n";
      //std::thread th(&ProgramInterpreter::Read, this, std::ref(str));
      //th.join(); 
      Read(str);
      std::cout << "Połączenie wątka sekcji\n\n"; 
    }
    else if(LineString == "End_Parallel_Actions"){
      std::cout << "Koniec sekcji\n\n";
      for(std::thread &thExec : currentThreads){
        if(thExec.joinable()) thExec.join();
      }
      return;
    }
    else if(Set4LibInterfaces.count(LineString) != 0){
      AbstractInterp4Command *pCmd = Set4LibInterfaces[LineString]->pCreateCmd();
      if(pCmd->ReadParams(str)){
        std::cout << "Zinterpretowane polecenie: ";
        pCmd->PrintCmd();
        std::cout << "\n";
        std::thread thExec(&AbstractInterp4Command::ExecCmd, pCmd, std::ref(scene), std::ref(comChannel));
        currentThreads.push_back(std::move(thExec));
      }
      else{
        std::cout << "Brak parametrów polecenia\n";
      }
    }
    else{
      std::cout << "Nie znane polecenie\n";
    }
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

  Read(textStream);
  return true;
}

bool ProgramInterpreter::Read_XML_Config(const char* fileName)
{
  Configuration conf;
  if (!ReadFile(fileName,conf)) return false;

  std::cout << "\nLista bibliotek do zaladowania:\n";
  std::list<std::string> lista = conf.getLibsNamesList();
  for(std::string name : lista) std::cout << name << "\n";
  std::cout << "\n";

  std::cout << "Lista wstepnych konfiguracji prostopadloscianow:\n";
  std::list<CubeConfiguration> lista2 = conf.getCubeConfigurationsList();
  for(CubeConfiguration name : lista2) name.printAllParams();
  std::cout << "\n";

  LoadLibraries(conf);
  LoadCubeConfiguration(conf);

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
    MobileObj *mobj = new MobileObj();
    mobj->LoadFromCubeConfiguration(cubeConf);
    scene.AddMobileObj(mobj);

    std::stringstream ss;
    ss << "AddObj Name=" << cubeConf.Name
       << " Shift=" << cubeConf.Shift
       << " Scale=" << cubeConf.Scale
       << " RotXYZ_deg=" << cubeConf.RotXYZ_deg
       << " Trans_m=" << cubeConf.Trans_m
       << " RGB=" << cubeConf.RGB << "\n";
    comChannel.LockAccess();
    comChannel.Send(ss.str().c_str());
    comChannel.UnlockAccess();
  }
}