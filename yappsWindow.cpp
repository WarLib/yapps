/*
-----------------------------------------------------------------------------
Filename:    yappsWindow.cpp
-----------------------------------------------------------------------------

This source file is part of the
___                 __    __ _ _    _
/___\__ _ _ __ ___  / / /\ \ (_) | _(_)
//  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
|___/
Tutorial Framework
http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#include "yappsWindow.h"
#include <OgreParticleSystem.h>
#include "fpscounter.hpp"

//-------------------------------------------------------------------------------------
yappsWindow::yappsWindow(void)
	: mRoot(0),
	mCamera(0),
//	mSceneMgr(0),
	mWindow(0),
	mResourcesCfg(Ogre::StringUtil::BLANK),
	mPluginsCfg(Ogre::StringUtil::BLANK),
	//mTrayMgr(0),
	mCameraMan(0),
	//mDetailsPanel(0),
	mCursorWasVisible(false),
	mShutDown(false),
	mInputManager(0),
	mMouse(0),
	mKeyboard(0) {
		yInputManager = Yapps::Input::getInstance();
}

//-------------------------------------------------------------------------------------

yappsWindow::~yappsWindow(void) {
	//	if (mTrayMgr) delete mTrayMgr;
	if (mCameraMan) delete mCameraMan;

	//Remove ourself as a Window listener
	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(mWindow);
	delete mRoot;
}

//-------------------------------------------------------------------------------------

bool yappsWindow::configure(void) {
	// Show the configuration dialog and initialise the system
	// You can skip this and use root.restoreConfig() to load configuration
	// settings if you were sure there are valid ones saved in ogre.cfg
	if (mRoot->restoreConfig()) {
		mWindow = mRoot->initialise(true, "Yapps");
		return true;
	} else if (mRoot->showConfigDialog()) {
		// If returned true, user clicked OK so initialise
		// Here we choose to let the system create a default rendering window by passing 'true'
		mWindow = mRoot->initialise(true, "Yapps");

		return true;
	} else {
		return false;
	}
}
//-------------------------------------------------------------------------------------

void yappsWindow::chooseSceneManager(void) {
	// Get the SceneManager, in this case a generic one
//	mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
}
//-------------------------------------------------------------------------------------

void yappsWindow::createCamera(void) {
	// Create the camera
	mCamera = ((Ogre::SceneManager*)(*GameState::getSingleton().GetActiveScene()))->getCamera(CAMERA_NAME);

	// Position it at 500 in Z direction
	//	mCamera->setPosition(Ogre::Vector3(0, 0, 80));
	mCamera->setPosition(Ogre::Vector3(-6636.61, 12.1833, 118330));
	// Look back along -Z
	mCamera->lookAt(Ogre::Vector3(0, 0, -300));
	mCamera->setNearClipDistance(1);
	mCamera->setFarClipDistance(800000000000);
	//	mCamera->setOrientationMode(Ogre::OR_PORTRAIT);
	mCameraMan = new OgreBites::SdkCameraMan(mCamera); // create a default camera controller

	FlightUI* ThisUi = FlightUI::getSingleton();
	ThisUi->Init(mCamera);

}
//-------------------------------------------------------------------------------------

void yappsWindow::createFrameListener(void) {
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	mInputManager = OIS::InputManager::createInputSystem(pl);

	mKeyboard = static_cast<OIS::Keyboard*> (mInputManager->createInputObject(OIS::OISKeyboard, true));
	mMouse = static_cast<OIS::Mouse*> (mInputManager->createInputObject(OIS::OISMouse, true));

	mMouse->setEventCallback(this);
	mKeyboard->setEventCallback(this);

	//Set initial mouse clipping size
	windowResized(mWindow);

	//Register as a Window listener
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	// create a params panel for displaying sample details
	Ogre::StringVector items;
	items.push_back("cam.pX");
	items.push_back("cam.pY");
	items.push_back("cam.pZ");
	items.push_back("");
	items.push_back("cam.oW");
	items.push_back("cam.oX");
	items.push_back("cam.oY");
	items.push_back("cam.oZ");
	items.push_back("");
	items.push_back("Filtering");
	items.push_back("Poly Mode");

	mRoot->addFrameListener(this);
}
//-------------------------------------------------------------------------------------

void yappsWindow::destroyScene(void) {
}
//-------------------------------------------------------------------------------------

void yappsWindow::createViewports(void) {
	// Create one viewport, entire window
/*	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	// Alter the camera aspect ratio to match the viewport
	mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
		*/
	GameState::getSingleton().SwitchScene(IN_GAME);
}
//-------------------------------------------------------------------------------------

void yappsWindow::setupResources(void) {
	// Load resource paths from config file
	Ogre::ConfigFile cf;
	cf.load(mResourcesCfg);

	// Go through all sections & settings in the file
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements()) {
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i) {
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				archName, typeName, secName);
		}
	}
}
//-------------------------------------------------------------------------------------

void yappsWindow::createResourceListener(void) {

}
//-------------------------------------------------------------------------------------

void yappsWindow::loadResources(void) {
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}
//-------------------------------------------------------------------------------------

void yappsWindow::go(void) {

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#ifdef _DEBUG
	mResourcesCfg = "ressources/etc/win_resources_d.cfg";
	mPluginsCfg = "ressources/etc/win_plugins_d.cfg";
#else
	mResourcesCfg = "ressources/etc/win_resources.cfg";
	mPluginsCfg = "ressources/etc/win_plugins.cfg";
#endif
#else
#ifdef _DEBUG
	mResourcesCfg = "ressources/etc/resources_d.cfg";
	mPluginsCfg = "ressources/etc/plugins_d.cfg";
#else
	mResourcesCfg = "ressources/etc/resources.cfg";
	mPluginsCfg = "ressources/etc/plugins.cfg";
#endif
#endif

	if (!setup())
		return;

	mRoot->startRendering();

	// clean up
	destroyScene();
}
//-------------------------------------------------------------------------------------

bool yappsWindow::setup(void) {
	mRoot = new Ogre::Root(mPluginsCfg);

	setupResources();

	bool carryOn = configure();
	if (!carryOn) return false;
	GameState::getSingleton().InjectRoot(mRoot,mWindow);
	GameState::getSingleton().SwitchScene(IN_GAME);

	chooseSceneManager();
	createCamera();
	createViewports();

	// Set default mipmap level (NB some APIs ignore this)
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	// Create any resource listeners (for loading screens)
	createResourceListener();
	// Load resources
	loadResources();

	// Create the scene
	createScene();

	createFrameListener();

	return true;
};
//-------------------------------------------------------------------------------------

bool yappsWindow::frameRenderingQueued(const Ogre::FrameEvent& evt) {
	if (mWindow->isClosed())
		return false;

	if (mShutDown)
		return false;

	//Need to capture/update each device
	mKeyboard->capture();
	mMouse->capture();


	// -------------- GUI TEST -----------------
	mCameraMan->frameRenderingQueued(evt); // if dialog isn't up, then update the camera

	Ui::GetActiveUi()->update(evt.timeSinceLastFrame,mCameraMan->getCamera()->getDerivedPosition());
	FPSCounter::GetInstance().InjectTime(evt.timeSinceLastFrame);
	return true;
}
//-------------------------------------------------------------------------------------

bool yappsWindow::keyPressed(const OIS::KeyEvent &arg) {
	yInputManager->publish(mKeyboard->getAsString(arg.key)); //***************** FANGEN DER KEYS

	if (arg.key == OIS::KC_F5) // refresh all textures
	{
		Ogre::TextureManager::getSingleton().reloadAll();
	} else if (arg.key == OIS::KC_SYSRQ) // take a screenshot
	{
		mWindow->writeContentsToTimestampedFile("screenshot", ".jpg");
	} else if (arg.key == OIS::KC_ESCAPE) {
		mShutDown = true;
	}
	//	CEGUI::System &sys = CEGUI::System::getSingleton();
	//	sys.injectKeyDown(arg.key);
	//	sys.injectChar(arg.text);
	mCameraMan->injectKeyDown(arg);
	return true;
}

bool yappsWindow::keyReleased(const OIS::KeyEvent &arg) {
	//CEGUI::System::getSingleton().injectKeyUp(arg.key);
	mCameraMan->injectKeyUp(arg);
	return true;
}

bool yappsWindow::mouseMoved(const OIS::MouseEvent &arg) {
	//CEGUI::System &sys = CEGUI::System::getSingleton();
	//sys.injectMouseMove(arg.state.X.rel, arg.state.Y.rel);
	// Scroll wheel.
	//	if (arg.state.Z.rel)
	//	sys.injectMouseWheelChange(arg.state.Z.rel / 120.0f);
	//	if (mTrayMgr->injectMouseMove(arg)) return true;
	mCameraMan->injectMouseMove(arg);
	return true;
}

bool yappsWindow::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
	//	if (mTrayMgr->injectMouseDown(arg, id)) return true;
	//CEGUI::System::getSingleton().injectMouseButtonDown(convertButton(id));
	mCameraMan->injectMouseDown(arg, id);
	return true;
}

bool yappsWindow::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
	//	if (mTrayMgr->injectMouseUp(arg, id)) return true;
	//CEGUI::System::getSingleton().injectMouseButtonUp(convertButton(id));
	mCameraMan->injectMouseUp(arg, id);
	return true;
}

//Adjust mouse clipping area

void yappsWindow::windowResized(Ogre::RenderWindow* rw) {
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

//Unattach OIS before window shutdown (very important under Linux)

void yappsWindow::windowClosed(Ogre::RenderWindow* rw) {
	//Only close for window that created OIS (the main window in these demos)
	if (rw == mWindow) {
		if (mInputManager) {
			mInputManager->destroyInputObject(mMouse);
			mInputManager->destroyInputObject(mKeyboard);

			OIS::InputManager::destroyInputSystem(mInputManager);
			mInputManager = 0;
		}
	}
}

void yappsWindow::createScene(void) {
	int n = 1000;
	Ogre::SceneManager* mSceneMgr = *GameState::getSingleton().GetActiveScene();
	string seed = "JulianUndTristanBauenYapps";
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.2f, 0.2f, 0.2f));
	mSceneMgr->setSkyBox(true, "MySky");

	FlightUI* ThisUi = FlightUI::getSingleton();

	Yapps::ControllableObject* TESTOBJEKT = new Yapps::Object(mSceneMgr, "Something", "carrier");
	yInputManager->subscribe(TESTOBJEKT);

	Galaxy & MyGalaxy(Galaxy::GetGalaxy(n, 8, seed, true));
	System** MySystems = MyGalaxy.GetSystems(n);

	StellarObject** MyObjects = MySystems[0]->GetObjects(n);

	for (int i = 0; i < n; i++) {
		std::stringstream name;
		name << "Object" << i;
		StellarObject & thisObject(*(MyObjects[i]));

		//Ogre::SceneNode* particleNode = mSceneMgr->getRootSceneNode()->crSieateChildSceneNode(name.str(),Ogre::Vector3(thisSystem.GetCenter().GetOrdinates(X),thisSystem.GetCenter().GetOrdinates(Y),thisSystem.GetCenter().GetOrdinates(Z)));
		Ogre::Entity* System = mSceneMgr->createEntity(name.str(), thisObject.GetMeshName());
		name << "node";
		//thisObject.GetCenter() *= 500.0;
		ThisUi->AddIndicator(MyObjects[i]);
		Ogre::SceneNode* SystemNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(name.str(), Ogre::Vector3(thisObject.GetCenter()));
		SystemNode->attachObject(System);

		cout << name.str() << " at " << thisObject.GetCenter() << endl;
		if (i == 0) {
			Ogre::ParticleSystem* sunParticle = mSceneMgr->createParticleSystem("Sun", "Space/Sun");
			Ogre::SceneNode* particleNode = SystemNode->createChildSceneNode("Particle");
			particleNode->attachObject(sunParticle);
		}

		SystemNode->scale(thisObject.GetRadius(), thisObject.GetRadius(), thisObject.GetRadius());
	}


	Ogre::Entity* LightBulb = mSceneMgr->createEntity("LightPos", "sphere.mesh");

	Ogre::SceneNode* Light1Node = mSceneMgr->getRootSceneNode()->createChildSceneNode("LightPosNode", Ogre::Vector3(-600.0f, 100.0f, 50.0f));
	Light1Node->attachObject(LightBulb);
	LightBulb->setCastShadows(false);
	Light1Node->scale(Ogre::Vector3(0.1,0.1,0.1));

	Ogre::Light* light1 = mSceneMgr->createLight("MainLight");
	light1->setPosition(-600.0f, 100.0f, 50.0f);


	Ogre::Entity* LightBulb2 = mSceneMgr->createEntity("LightPos2", "sphere.mesh");

	Ogre::SceneNode* Light2Node = mSceneMgr->getRootSceneNode()->createChildSceneNode("LightPos2Node", Ogre::Vector3(-500.0f, 120.0f, -600.0f));
	Light2Node->attachObject(LightBulb2);
	LightBulb2->setCastShadows(false);
	Light2Node->scale(Ogre::Vector3(0.1,0.1,0.1));

	Ogre::Light* light2 = mSceneMgr->createLight("SecondLight");
	light2->setPosition(-500.0f, 120.0f, -50.0f);

	ThisUi->Show();
}

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

	int main(int argc, char *argv[]) {
		yappsWindow app;
		try {
			app.go();
		} catch (Ogre::Exception& e) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
			std::cerr << "An exception has occured: " <<
				e.getFullDescription().c_str() << std::endl;
#endif
		}

		return 0;
	}

#ifdef __cplusplus
}
#endif



