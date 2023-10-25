#include "Preprocessor.hh"
#include <iostream>

void Preprocessor::RemoveComments(std::string& text)
{
    unsigned i = 0;
  while(i < text.length() - 2)
  {
    if(text[i] == '/' && text[i+1] == '*'){
      unsigned k = i+2;
      while(k < text.length() - 2){
        if(text[k] == '*' && text[k+1] == '/'){
          text.erase(i,k+2-i);
          break;
        }
        k++;
      }
    }
    if(text[i] == '/' && text[i+1] == '/'){
      unsigned k = i+2;
      while(k < text.length() - 2){
        if(text[k] == '\n'){
          text.erase(i,k-i);
          break;
        }
        k++;
      }
    }
    i++;
  }
}

std::stringstream Preprocessor::RunPreprocessor(std::stringstream& cmdListStream)
{
  std::string text = cmdListStream.str();
  Preprocessor::RemoveComments(text);
  Preprocessor::RemoveEmptyLines(text);

  unsigned i = 0;
  while(i < text.length() - 1)
  {
    if(text[i] == '#'){
      if(text.substr(i+1,6) == "define"){
        int a = i+7;
        while(text[a] == ' ') a++;
        int k = a;
        while(text[k] != ' ' && text[k] != '\n' && text[k] != '(') k++;
        std::string macroName = text.substr(a,k-a);
        if(text[k] == ' ' || text[k] == '\n')
          k = Preprocessor::DefineReplace(text, macroName, k);
        /*else
          k = Preprocessor::DefineReplaceArgs(text, macroName, k);*/
        text.erase(i,k-i);
      }
    }
    i++;
  }
  std::stringstream textStream;
  textStream << text;
  return textStream;
}

int Preprocessor::DefineReplace(std::string& text, std::string macroName, int i)
{
  while(text[i] == ' ') i++;
  int k = i;

  bool nextLine = false;
  while(text[k] != '\n' || nextLine){
    if(text[k] == '\\'){
      nextLine = true;
      text.erase(k,1);
    } 
    if(text[k] == '\n') nextLine = false;
    k++;
  }
  std::string macroValue = text.substr(i,k-i);
  int pos = k-1;
  while((pos = text.find(macroName, pos)) != (int)std::string::npos){
    text.replace(pos,macroName.length(),macroValue);
    pos += macroValue.length();
  }
  return k;
}

void Preprocessor::RemoveEmptyLines(std::string& text)
{
  int pos;
  while((pos = text.find("\n\n",0)) != (int)std::string::npos) 
    text.erase(pos,1);
}
