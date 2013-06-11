
#include "Object.h"


using namespace Yapps;
Object::Object(Ogre::SceneManager* mSceneMgr, std::string name, std::string type){
        this->mSceneMgr = mSceneMgr;
        std::string endungMesh = ".mesh";
        std::string myMesh = type+endungMesh;
        mEntity = mSceneMgr->createEntity(name.c_str(), myMesh.c_str());
        mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(name, Ogre::Vector3(0,0,0)); //+Position!
        mMainNode->attachObject(mEntity);

        mMainNode->scale(0.1,0.1,0.1);

        Funktor* forward = new mv_forward();
        forward->setParent(this);
        abilities.push_back(forward);
        bind("forward",forward);

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
 std::cout <<"YEHAW"<< std::endl;

return ;
 }
