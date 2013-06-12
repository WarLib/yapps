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
#include <map>
#include <list>

namespace Yapps
{
class Object;
};

#include "Funktor.h"
#include "ControllableObject.h"

#include "../environment/world.hpp"
#include "../physics/physics.h"

namespace Yapps
{




class Object:  public ControllableObject
{
public:
    Ogre::SceneNode *mMainNode; // Main Physical node
    Ogre::SceneNode *mSightNode; // "Sight" node - The character is supposed to be looking here
    Ogre::SceneNode *mCameraNode; // Node for the chase camera
    Ogre::Entity *mEntity; // Character entity
    Ogre::SceneManager *mSceneMgr; // Point of insertion

    physicalEntity* physicalMe;

    std::list<Yapps::Funktor*> abilities;
    std::list<Yapps::Funktor*> tellMeAboutFrames;


    Yapps::Vec3 position;

    Yapps::Vec3 Rotation;
    Yapps::Vec3 Bewegung;

    virtual void frame(Ogre::Real elapsed);


    Object(Ogre::SceneManager* mSceneMgr, std::string name, std::string type, Vec3 pos = Vec3(0,0,0) );

    Ogre::SceneNode *getSightNode();
    Ogre::SceneNode *getCameraNode();
    Ogre::Vector3 getWorldPosition();

private:


protected:

};

};

#endif
