
#include "yappsObject.h"


yappsObject::yappsObject(Ogre::SceneManager* mSceneMgr, std::string name, std::string type){
        this->mSceneMgr = mSceneMgr;
        std::string endungMesh = ".mesh";
        std::string myMesh = type+endungMesh;
        mEntity = mSceneMgr->createEntity(name.c_str(), myMesh.c_str());
        mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(name, Ogre::Vector3(0,0,0)); //+Position!
        mMainNode->attachObject(mEntity);

        mMainNode->scale(1,1,1);

}


Ogre::SceneNode *yappsObject::getSightNode() {
    return mSightNode;
}

Ogre::SceneNode *yappsObject::getCameraNode() {
    return mCameraNode;
}

Ogre::Vector3 yappsObject::getWorldPosition() {
    return mMainNode->_getDerivedPosition();
}
