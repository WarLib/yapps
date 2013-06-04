#ifndef _CHAR_HPP
#define _CHAR_HPP


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

using namespace Ogre;

class Char {
    // Attributes ------------------------------------------------------------------------------
protected:
    SceneNode *mMainNode; // Main character node
    SceneNode *mSightNode; // "Sight" node - The character is supposed to be looking here
    SceneNode *mCameraNode; // Node for the chase camera
    Entity *mEntity; // Character entity
    SceneManager *mSceneMgr;

public:
    // Methods ---------------------------------------------------------------------------------
protected:
public:
    // Updates the character (movement...)
    virtual void update(Real elapsedTime, OIS::Keyboard *input) = 0;
    // The three methods below returns the two camera-related nodes, 
    // and the current position of the character (for the 1st person camera)
    SceneNode *getSightNode();
    SceneNode *getCameraNode();
    Vector3 getWorldPosition();
};
#endif