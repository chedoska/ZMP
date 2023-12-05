#ifndef SCENE_HH
#define SCENE_HH

#include "AbstractScene.hh"
#include <map>
#include <memory>
#include "MobileObj.hh"

class Scene : public AbstractScene
{
public:
    Scene();
    AbstractMobileObj* FindMobileObj(const char *sName) override;
    void AddMobileObj(AbstractMobileObj *pMobObj) override;
    ~Scene();

private:
    std::map<std::string,AbstractMobileObj*> Set_MobileObjs;
};

#endif