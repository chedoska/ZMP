#ifndef MOBILEOBJ_HH
#define MOBILEOBJ_HH

#include "AbstractMobileObj.hh"
#include "Configuration.hh"
#include <thread>
#include <chrono>
#include <mutex>

class MobileObj : public AbstractMobileObj
{
public:
    ~MobileObj();
    double GetAng_Roll_deg() const override;
    double GetAng_Pitch_deg() const override;
    double GetAng_Yaw_deg() const override;
    void SetAng_Roll_deg(double Ang_Roll_deg) override;
    void SetAng_Pitch_deg(double Ang_Pitch_deg) override;
    void SetAng_Yaw_deg(double Ang_Yaw_deg) override;
    const Vector3D & GetPositoin_m() const override;
    void SetPosition_m(const Vector3D &rPos) override;
    void SetName(const char* sName) override;
    const std::string & GetName() const override;
    void LoadFromCubeConfiguration(CubeConfiguration &configuration);

    std::mutex &UseGuard() override;

private:
    CubeConfiguration m_objData;
    std::mutex m_mutex;
};

#endif