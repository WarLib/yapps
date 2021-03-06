#ifndef _CAMERA_HPP
#define _CAMERA_HPP
// Our extended camera class
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

class ExtendedCamera {
    // Attributes ------------------------------------------------------------------------------
protected:
    SceneNode *mTargetNode; // The camera target
    SceneNode *mCameraNode; // The camera itself
    Camera *mCamera; // Ogre camera

    SceneManager *mSceneMgr;
    String mName;

    bool mOwnCamera; // To know if the ogre camera binded has been created outside or inside of this class

    Real mTightness; // Determines the movement of the camera - 1 means tight movement, while 0 means no movement
public:
    // Methods ---------------------------------------------------------------------------------
protected:
public:
    ExtendedCamera(String name, SceneManager *sceneMgr, Camera *camera = 0);
    ~ExtendedCamera();

    void setTightness(Real tightness);
    Real getTightness();
    Vector3 getCameraPosition();
    void instantUpdate(Vector3 cameraPosition, Vector3 targetPosition);
    void update(Real elapsedTime, Vector3 cameraPosition, Vector3 targetPosition);
};
#endif