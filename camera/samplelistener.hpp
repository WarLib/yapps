#ifndef _SAMPLELISTENER_HPP
#define _SAMPLELISTENER_HPP




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
#include <ExampleFrameListener.h>

#include "camera.hpp"
#include "../entities/player.hpp"

using namespace Ogre;

class SampleListener : public ExampleFrameListener {
protected:
    // References to the main character and the camera
    Char *mChar;
    ExtendedCamera *mExCamera;

    // Camera mode - Now supports 1st person, 3rd person (chasing) and 3rd person (fixed)
    unsigned int mMode;

public:
    SampleListener(RenderWindow* win, Camera* cam);

    void setCharacter(Char *character);

    void setExtendedCamera(ExtendedCamera *cam);

    bool frameStarted(const FrameEvent& evt);
};

#endif