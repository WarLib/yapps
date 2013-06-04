#include "environment/world.hpp"
#include "entities/player.hpp"
#include "camera/camera.hpp"
#include "camera/samplelistener.hpp"

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
#include <ExampleApplication.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>


class MainApp: public ExampleApplication {
public:
	MainApp();
	~MainApp();
protected:
	// Just override the mandatory create scene method
	void createScene(void);
	void destroyScene(void);
	void createFrameListener(void);
};
