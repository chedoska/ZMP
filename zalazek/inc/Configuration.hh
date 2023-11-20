#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include <list>
#include <string>

class Configuration {
public:
  void addLibName(std::string libName) {m_libsNames.push_back(libName);}
  std::list<std::string> getLibsNamesList() {return m_libsNames;}

private:
  std::list<std::string> m_libsNames;
};


#endif
