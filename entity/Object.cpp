
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
        tempPos[0]=0;tempPos[1]=0;tempPos[2]=0;

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


void Object::callback(){
//Do stuff here you have to do on any frame


}
