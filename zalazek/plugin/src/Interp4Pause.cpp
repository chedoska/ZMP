#include <iostream>
#include "Interp4Pause.hh"

using std::cout;
using std::endl;

extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Pause"; }
}

/*!
 * \brief
 *
 *
 */
AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Pause::CreateCmd();
}

/*!
 *
 */
Interp4Pause::Interp4Pause():
  _PauseTime_ms(0)
{}

/*!
 *
 */
void Interp4Pause::PrintCmd() const
{
  cout << GetCmdName() << " " << _PauseTime_ms << endl; 
}

/*!
 *
 */
const char* Interp4Pause::GetCmdName() const
{
  return ::GetCmdName();
}

/*!
 *
 */
bool Interp4Pause::ExecCmd( AbstractScene      &rScn, 
                           const char         *sMobObjName,
			   AbstractComChannel &rComChann
			 )
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}

/*!
 *
 */
bool Interp4Pause::ReadParams(std::istream& Strm_CmdsList)
{
  if(Strm_CmdsList >> _PauseTime_ms)
    return true;
  else
    return false;
}

/*!
 *
 */
AbstractInterp4Command* Interp4Pause::CreateCmd()
{
  return new Interp4Pause();
}

/*!
 *
 */
void Interp4Pause::PrintSyntax() const
{
  cout << "   Pause  Czas_Pauzy[ms]" << endl;
}
