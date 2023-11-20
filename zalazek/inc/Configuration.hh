#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include "Vector3D.hh"

#include <list>
#include <string>

struct CubeConfiguration {
  std::string Name;
  Vector3D Shift;
  Vector3D Scale;
  Vector3D RotXYZ_deg;
  Vector3D Trans_m;
  Vector3D RGB;
};

class Configuration {
public:
  void addLibName(std::string libName) {m_libsNames.push_back(libName);}
  void addCubeConfiguration(CubeConfiguration cubeConfiguration) {m_cubeConfigs.push_back(cubeConfiguration);}
  std::list<std::string> getLibsNamesList() {return m_libsNames;}
  std::list<CubeConfiguration> getCubeConfigurationsList() {return m_cubeConfigs;}

private:
  std::list<std::string> m_libsNames;
  std::list<CubeConfiguration> m_cubeConfigs;
};


#endif
