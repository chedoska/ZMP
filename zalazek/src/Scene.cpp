#include "Scene.hh"

Scene::Scene()
{

}

AbstractMobileObj* Scene::FindMobileObj(const char *sName)
{
    if(Set_MobileObjs.find(sName) != Set_MobileObjs.end())
        return Set_MobileObjs[sName];
    return nullptr;
}

void Scene::AddMobileObj(AbstractMobileObj *pMobObj)
{
    Set_MobileObjs[pMobObj->GetName()] = pMobObj;
}

Scene::~Scene()
{
    std::map<std::string, AbstractMobileObj*>::iterator it;
    for(it = Set_MobileObjs.begin(); it != Set_MobileObjs.end(); it++)
        if(it->second) delete it->second;
}