#include <iostream>
#include "Interp4Move.hh"
#include <string>
#include <sstream>
#include <thread>
#include <cmath>

using std::cout;
using std::endl;

#define MOVE_RES_PER_SEC 20

extern "C" {
  AbstractInterp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Move"; }
}

double dtor(double deg)
{
  return deg * (M_PI / 180.0);
}

Vector3D rotateXYZ(Vector3D &vec, double or_x, double or_y, double or_z)
{
  Vector3D res;
  res[0] = cos(or_y)*cos(or_z)*vec[0]-cos(or_y)*sin(or_z)*vec[1]+sin(or_y)*vec[2];
  res[1] = (cos(or_x)*sin(or_z)+cos(or_z)*sin(or_x)*sin(or_y))*vec[0]+
           (cos(or_x)*cos(or_z)-sin(or_x)*sin(or_y)*sin(or_z))*vec[1]-
           cos(or_y)*sin(or_x)*vec[2];
  res[2] = (sin(or_x)*sin(or_z)-cos(or_x)*cos(or_z)*sin(or_y))*vec[0]+
           (cos(or_z)*sin(or_x)+cos(or_x)*sin(or_y)*sin(or_z))*vec[1]+
           cos(or_x)*cos(or_y)*vec[2];
  return res;
}

/*!
 * \brief
 *
 *
 */
AbstractInterp4Command* CreateCmd(void)
{
  return Interp4Move::CreateCmd();
}

/*!
 *
 */
Interp4Move::Interp4Move(): _Speed_mmS(0), _Distance(0), _ObjectName("")
{}

/*!
 *
 */
void Interp4Move::PrintCmd() const
{
  cout << GetCmdName() << " " << _ObjectName << " " << _Speed_mmS << " " << _Distance << endl;
}

/*!
 *
 */
const char* Interp4Move::GetCmdName() const
{
  return ::GetCmdName();
}

/*!
 *
 */
bool Interp4Move::ExecCmd( AbstractScene      &rScn, 
			   AbstractComChannel &rComChann
			 )
{
  AbstractMobileObj *pObj = rScn.FindMobileObj(_ObjectName.c_str());
  if(pObj == nullptr)
  {
    std::cout << "Nie znaleziono obiektu na scenie: " << _ObjectName << "\n";
    return false;
  }

  double time_of_move = _Distance/abs(_Speed_mmS);
  int iterations_num = time_of_move*MOVE_RES_PER_SEC;
  double dist_per_step = _Speed_mmS/(double)MOVE_RES_PER_SEC;
  int time_step_ms = (int)((time_of_move/(double)iterations_num)*1000.0);

  for(int i = 0; i < iterations_num; i++)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(time_step_ms));
    std::lock_guard<std::mutex> Guard(pObj->UseGuard());

    Vector3D straight = createVector3D(dist_per_step,0,0);
    Vector3D vec = rotateXYZ(straight, dtor(pObj->GetAng_Roll_deg()),
      dtor(pObj->GetAng_Pitch_deg()), dtor(pObj->GetAng_Yaw_deg()));

    pObj->SetPosition_m(pObj->GetPositoin_m() + vec);

    std::stringstream ss;
    ss << "UpdateObj Name=" << _ObjectName
       << " Trans_m=" << pObj->GetPositoin_m() << "\n";
    rComChann.LockAccess();
    rComChann.Send(ss.str().c_str());
    rComChann.UnlockAccess();
  }
  return true;
}

/*!
 *
 */
bool Interp4Move::ReadParams(std::istream& Strm_CmdsList)
{
  if(Strm_CmdsList >> _ObjectName >> _Speed_mmS >> _Distance)
    return true;
  else
    return false;
}

/*!
 *
 */
AbstractInterp4Command* Interp4Move::CreateCmd()
{
  return new Interp4Move();
}

/*!
 *
 */
void Interp4Move::PrintSyntax() const
{
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}
