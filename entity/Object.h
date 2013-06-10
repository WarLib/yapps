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

namespace Yapps {
class Object;
};

#include "Funktor.h"
#include "ControllableObject.h"

#include "../environment/world.hpp"

namespace Yapps {
class Object: public ControllableObject {
    public:
        Ogre::SceneNode *mMainNode; // Main Physical node
        Ogre::SceneNode *mSightNode; // "Sight" node - The character is supposed to be looking here
        Ogre::SceneNode *mCameraNode; // Node for the chase camera
        Ogre::Entity *mEntity; // Character entity
        Ogre::SceneManager *mSceneMgr; // Point of insertion

        std::list<Yapps::Funktor*> abilities;

        Yapps::Vec3 bla;

        double tempPos[3];

        void callback();

        Object(Ogre::SceneManager* mSceneMgr, std::string name, std::string type);

        Ogre::SceneNode *getSightNode();
        Ogre::SceneNode *getCameraNode();
        Ogre::Vector3 getWorldPosition();

    private:


    protected:

    };

};

#endif
