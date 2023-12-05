#include <iostream>
#include "Interp4Rotate.hh"
#include <string>
#include <sstream>
#include <thread>

using std::cout;
using std::endl;

#define ROTATE_RES_PER_SEC 20

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
			   AbstractComChannel &rComChann
			 )
{
  AbstractMobileObj *pObj = rScn.FindMobileObj(_ObjectName.c_str());
  if(pObj == nullptr)
  {
    std::cout << "Nie znaleziono obiektu na scenie: " << _ObjectName << "\n";
    return false;
  }

  double time_of_move = _Angle/abs(_AngularVelocity);
  int iterations_num = time_of_move*ROTATE_RES_PER_SEC;
  double ang_per_step = _AngularVelocity/(double)ROTATE_RES_PER_SEC;
  int time_step_ms = (int)((time_of_move/(double)iterations_num)*1000.0);

  for(int i = 0; i < iterations_num; i++)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(time_step_ms));
    std::lock_guard<std::mutex> Guard(pObj->UseGuard());
    if(_AxisName == "OX")
      pObj->SetAng_Roll_deg(pObj->GetAng_Roll_deg() + ang_per_step);
    else if(_AxisName == "OY")
      pObj->SetAng_Pitch_deg(pObj->GetAng_Pitch_deg() + ang_per_step);
    else if(_AxisName == "OZ")
      pObj->SetAng_Yaw_deg(pObj->GetAng_Yaw_deg() + ang_per_step);

    Vector3D rotVec = createVector3D(pObj->GetAng_Roll_deg(),
      pObj->GetAng_Pitch_deg(), pObj->GetAng_Yaw_deg());

    std::stringstream ss;
    ss << "UpdateObj Name=" << _ObjectName
       << " RotXYZ_deg=" << rotVec << "\n";
    rComChann.LockAccess();
    rComChann.Send(ss.str().c_str());
    rComChann.UnlockAccess();
  }
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
