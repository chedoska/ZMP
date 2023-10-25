#include <iostream>
#include "Interp4Rotate.hh"

using std::cout;
using std::endl;

extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Rotate"; }
}

/*!
 * \brief
 *
 *
 */
AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Rotate::CreateCmd();
}

/*!
 *
 */
Interp4Rotate::Interp4Rotate():
  _ObjectName(""), _AxisName("OX"), _AngularVelocity(0), _Angle(0)
{}

/*!
 *
 */
void Interp4Rotate::PrintCmd() const
{
  cout << GetCmdName() << " " << _ObjectName << " " << _AxisName << " " << _AngularVelocity
       << " " << _Angle << endl; 
}

/*!
 *
 */
const char* Interp4Rotate::GetCmdName() const
{
  return ::GetCmdName();
}

/*!
 *
 */
bool Interp4Rotate::ExecCmd( AbstractScene      &rScn, 
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
bool Interp4Rotate::ReadParams(std::istream& Strm_CmdsList)
{
  if(Strm_CmdsList >> _ObjectName >> _AxisName >> _AngularVelocity >> _Angle)
    return true;
  else
    return false;
}

/*!
 *
 */
AbstractInterp4Command* Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}

/*!
 *
 */
void Interp4Rotate::PrintSyntax() const
{
  cout << "   Rotate  NazwaObiektu NazwaOsi Szybkosc_kat[deg/s] Kat[deg]" << endl;
}
