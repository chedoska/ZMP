#include <iostream>
#include "Interp4Set.hh"

using std::cout;
using std::endl;

extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Set"; }
}

/*!
 * \brief
 *
 *
 */
AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Set::CreateCmd();
}

/*!
 *
 */
Interp4Set::Interp4Set():
  _ObjectName(""), _X(0), _Y(0), _Z(0), _or_X(0), _or_Y(0), _or_Z(0)
{}

/*!
 *
 */
void Interp4Set::PrintCmd() const
{
  cout << GetCmdName() << " " << _ObjectName << " " << _X << " " << _Y << " " << _Z
       << " " << _or_X << " " << _or_Y << " " << _or_Z << endl; 
}

/*!
 *
 */
const char* Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}

/*!
 *
 */
bool Interp4Set::ExecCmd( AbstractScene      &rScn, 
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
bool Interp4Set::ReadParams(std::istream& Strm_CmdsList)
{
  if(Strm_CmdsList >> _ObjectName >> _X >> _Y >> _Z >> _or_X >> _or_Y >> _or_Z)
    return true;
  else
    return false;
}

/*!
 *
 */
AbstractInterp4Command* Interp4Set::CreateCmd()
{
  return new Interp4Set();
}

/*!
 *
 */
void Interp4Set::PrintSyntax() const
{
  cout << "   Set  NazwaObiektu wsp_x[m] wsp_y[m] wsp_z[m] kat_OX[deg] kat_OY[deg] kat_OZ[deg]" << endl;
}
