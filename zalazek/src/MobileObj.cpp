#include "MobileObj.hh"

MobileObj::~MobileObj()
{
    std::cout << "DEstructor called\n";
}

double MobileObj::GetAng_Roll_deg() const
{
    return m_objData.RotXYZ_deg[0];
}

double MobileObj::GetAng_Pitch_deg() const
{
    return m_objData.RotXYZ_deg[1];
}

double MobileObj::GetAng_Yaw_deg() const
{
    return m_objData.RotXYZ_deg[2];
}
    
void MobileObj::SetAng_Roll_deg(double Ang_Roll_deg)
{
    m_objData.RotXYZ_deg[0] = Ang_Roll_deg;
}

void MobileObj::SetAng_Pitch_deg(double Ang_Pitch_deg)
{
    m_objData.RotXYZ_deg[1] = Ang_Pitch_deg;
}

void MobileObj::SetAng_Yaw_deg(double Ang_Yaw_deg)
{
    m_objData.RotXYZ_deg[2] = Ang_Yaw_deg; 
}

const Vector3D & MobileObj::GetPositoin_m() const
{
    return m_objData.Trans_m;
} 

void MobileObj::SetPosition_m(const Vector3D &rPos)
{
    m_objData.Trans_m = rPos;
}

void MobileObj::SetName(const char* sName) 
{
    m_objData.Name = sName;
}

const std::string & MobileObj::GetName() const
{
    return m_objData.Name;
}

void MobileObj::LoadFromCubeConfiguration(CubeConfiguration &configuration)
{
    m_objData = configuration;
}

std::mutex& MobileObj::UseGuard()
{
    return m_mutex;
}