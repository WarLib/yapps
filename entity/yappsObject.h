#ifndef __yappsObject_h_
#define __yappsObject_h_


//Bruteforce importing

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>


#include <string>

#include "../yappsControllableObject.h"

class yappsObject: public yappsControllableObject{
public:
    Ogre::SceneNode *mMainNode; // Main Physical node
    Ogre::SceneNode *mSightNode; // "Sight" node - The character is supposed to be looking here
    Ogre::SceneNode *mCameraNode; // Node for the chase camera
    Ogre::Entity *mEntity; // Character entity
    Ogre::SceneManager *mSceneMgr; // Point of insertion


    yappsObject(Ogre::SceneManager* mSceneMgr, std::string name, std::string type);

    Ogre::SceneNode *getSightNode();
    Ogre::SceneNode *getCameraNode();
    Ogre::Vector3 getWorldPosition();
private:


protected:

};



#endif
