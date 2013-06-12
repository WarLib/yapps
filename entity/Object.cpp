
#include "Object.h"


using namespace Yapps;
Object::Object(Ogre::SceneManager* mSceneMgr, std::string name, std::string type, Vec3 pos){
        this->mSceneMgr = mSceneMgr;
        std::string endungMesh = ".mesh";
        std::string myMesh = type+endungMesh;
        mEntity = mSceneMgr->createEntity(name.c_str(), myMesh.c_str());
        mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(name, position ); //+Position!
        mMainNode->attachObject(mEntity);

        mMainNode->scale(0.06,0.06,0.06);



        Funktor* rotDown = new trn_pitch_d();
        rotDown->setParent(this);
        abilities.push_back(rotDown);
        bind("down",rotDown);

        Funktor* rotUp = new trn_pitch_u();
        rotUp->setParent(this);
        abilities.push_back(rotUp);
        bind("up",rotUp);

        Funktor* rotLeft = new trn_yaw_l();
        rotLeft->setParent(this);
        abilities.push_back(rotLeft);
        bind("left",rotLeft);

        Funktor* rotRight = new trn_yaw_r();
        rotRight->setParent(this);
        abilities.push_back(rotRight);
        bind("right",rotRight);

        Funktor* fwd = new mv_accelerate();
        fwd->setParent(this);
        abilities.push_back(fwd);
        bind("accelerate",fwd);


        Funktor* rotlis = new rot_inertialistener();
        rotlis->setParent(this);
        abilities.push_back(rotlis);

        Funktor* mvlis = new mv_inertialistener();
        mvlis->setParent(this);
        abilities.push_back(mvlis);

        tellMeAboutFrames.push_back(mvlis);
        tellMeAboutFrames.push_back(rotlis);

        position = pos;
        physicalMe = new physicalEntity(position);

}


Ogre::SceneNode *Object::getSightNode() {
    return mSightNode;
}

Ogre::SceneNode *Object::getCameraNode() {
    return mCameraNode;
}

Ogre::Vector3 Object::getWorldPosition() {
    return mMainNode->_getDerivedPosition();
}



void Object::frame(Ogre::Real elapsed){

    position = physicalMe->toYVec3();
    //std::cout << position << std::endl;
for (std::list<Funktor*>::iterator iter = tellMeAboutFrames.begin(); iter != tellMeAboutFrames.end(); ++iter)
    (*iter)->frame(elapsed);

    mMainNode->setPosition(position);
    mMainNode->setOrientation( physicalMe->toQuat() );
return ;
 }
