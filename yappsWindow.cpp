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

//-------------------------------------------------------------------------------------

yappsWindow::yappsWindow(void)
: mRoot(0),
mCamera(0),
mSceneMgr(0),
mWindow(0),
mResourcesCfg(Ogre::StringUtil::BLANK),
mPluginsCfg(Ogre::StringUtil::BLANK),
mTrayMgr(0),
mCameraMan(0),
mDetailsPanel(0),
mCursorWasVisible(false),
mShutDown(false),
mInputManager(0),
mMouse(0),
mKeyboard(0) {
    yInputManager = yappsInput::getInstance();


}

//-------------------------------------------------------------------------------------

yappsWindow::~yappsWindow(void) {
    if (mTrayMgr) delete mTrayMgr;
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
    if (mRoot->showConfigDialog()) {
        // If returned true, user clicked OK so initialise
        // Here we choose to let the system create a default rendering window by passing 'true'
        mWindow = mRoot->initialise(true, "TutorialApplication Render Window");

        return true;
    } else {
        return false;
    }
}
//-------------------------------------------------------------------------------------

void yappsWindow::chooseSceneManager(void) {
    // Get the SceneManager, in this case a generic one
    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
}
//-------------------------------------------------------------------------------------

void yappsWindow::createCamera(void) {
    // Create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");

    // Position it at 500 in Z direction
    mCamera->setPosition(Ogre::Vector3(0, 0, 80));
    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0, 0, -300));
    mCamera->setNearClipDistance(5);

    mCameraMan = new OgreBites::SdkCameraMan(mCamera); // create a default camera controller
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

    mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", mWindow, mMouse, this);
    mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
    mTrayMgr->hideCursor();

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

    mDetailsPanel = mTrayMgr->createParamsPanel(OgreBites::TL_NONE, "DetailsPanel", 200, items);
    mDetailsPanel->setParamValue(9, "Bilinear");
    mDetailsPanel->setParamValue(10, "Solid");
    mDetailsPanel->hide();

    mRoot->addFrameListener(this);
}
//-------------------------------------------------------------------------------------

void yappsWindow::destroyScene(void) {
}
//-------------------------------------------------------------------------------------

void yappsWindow::createViewports(void) {
    // Create one viewport, entire window
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
            Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
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
#ifdef _DEBUG
    mResourcesCfg = "ressources/etc/resources_d.cfg";
    mPluginsCfg = "ressources/etc/plugins_d.cfg";
#else
    mResourcesCfg = "ressources/etc/resources.cfg";
    mPluginsCfg = "ressources/etc/plugins.cfg";
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

    mTrayMgr->frameRenderingQueued(evt);

    if (!mTrayMgr->isDialogVisible()) {
        mCameraMan->frameRenderingQueued(evt); // if dialog isn't up, then update the camera
        if (mDetailsPanel->isVisible()) // if details panel is visible, then update its contents
        {
            mDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(mCamera->getDerivedPosition().x));
            mDetailsPanel->setParamValue(1, Ogre::StringConverter::toString(mCamera->getDerivedPosition().y));
            mDetailsPanel->setParamValue(2, Ogre::StringConverter::toString(mCamera->getDerivedPosition().z));
            mDetailsPanel->setParamValue(4, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().w));
            mDetailsPanel->setParamValue(5, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().x));
            mDetailsPanel->setParamValue(6, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().y));
            mDetailsPanel->setParamValue(7, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().z));
        }
    }

    return true;
}
//-------------------------------------------------------------------------------------

bool yappsWindow::keyPressed(const OIS::KeyEvent &arg) {
    yInputManager->publish(mKeyboard->getAsString(arg.key)); //***************** FANGEN DER KEYS

    if (mTrayMgr->isDialogVisible()) return true; // don't process any more keys if dialog is up

    if (arg.key == OIS::KC_F) // toggle visibility of advanced frame stats
    {
        mTrayMgr->toggleAdvancedFrameStats();
    } else if (arg.key == OIS::KC_G) // toggle visibility of even rarer debugging details
    {
        if (mDetailsPanel->getTrayLocation() == OgreBites::TL_NONE) {
            mTrayMgr->moveWidgetToTray(mDetailsPanel, OgreBites::TL_TOPRIGHT, 0);
            mDetailsPanel->show();
        } else {
            mTrayMgr->removeWidgetFromTray(mDetailsPanel);
            mDetailsPanel->hide();
        }
    } else if (arg.key == OIS::KC_T) // cycle polygon rendering mode
    {
        Ogre::String newVal;
        Ogre::TextureFilterOptions tfo;
        unsigned int aniso;

        switch (mDetailsPanel->getParamValue(9).asUTF8()[0]) {
            case 'B':
                newVal = "Trilinear";
                tfo = Ogre::TFO_TRILINEAR;
                aniso = 1;
                break;
            case 'T':
                newVal = "Anisotropic";
                tfo = Ogre::TFO_ANISOTROPIC;
                aniso = 8;
                break;
            case 'A':
                newVal = "None";
                tfo = Ogre::TFO_NONE;
                aniso = 1;
                break;
            default:
                newVal = "Bilinear";
                tfo = Ogre::TFO_BILINEAR;
                aniso = 1;
        }

        Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(tfo);
        Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(aniso);
        mDetailsPanel->setParamValue(9, newVal);
    } else if (arg.key == OIS::KC_R) // cycle polygon rendering mode
    {
        Ogre::String newVal;
        Ogre::PolygonMode pm;

        switch (mCamera->getPolygonMode()) {
            case Ogre::PM_SOLID:
                newVal = "Wireframe";
                pm = Ogre::PM_WIREFRAME;
                break;
            case Ogre::PM_WIREFRAME:
                newVal = "Points";
                pm = Ogre::PM_POINTS;
                break;
            default:
                newVal = "Solid";
                pm = Ogre::PM_SOLID;
        }

        mCamera->setPolygonMode(pm);
        mDetailsPanel->setParamValue(10, newVal);
    } else if (arg.key == OIS::KC_F5) // refresh all textures
    {
        Ogre::TextureManager::getSingleton().reloadAll();
    } else if (arg.key == OIS::KC_SYSRQ) // take a screenshot
    {
        mWindow->writeContentsToTimestampedFile("screenshot", ".jpg");
    } else if (arg.key == OIS::KC_ESCAPE) {
        mShutDown = true;
    }

    mCameraMan->injectKeyDown(arg);
    return true;
}

bool yappsWindow::keyReleased(const OIS::KeyEvent &arg) {
    mCameraMan->injectKeyUp(arg);
    return true;
}

bool yappsWindow::mouseMoved(const OIS::MouseEvent &arg) {
    if (mTrayMgr->injectMouseMove(arg)) return true;
    mCameraMan->injectMouseMove(arg);
    return true;
}

bool yappsWindow::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
    if (mTrayMgr->injectMouseDown(arg, id)) return true;
    mCameraMan->injectMouseDown(arg, id);
    return true;
}

bool yappsWindow::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) {
    if (mTrayMgr->injectMouseUp(arg, id)) return true;
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
    string seed = "magicrootseed";
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
    mSceneMgr->setSkyBox(true, "MySky");

    yappsControllableObject* TESTOBJEKT = new yappsObject(mSceneMgr, "Something", "yappsShip");
    yInputManager->subscribe(TESTOBJEKT);

    Galaxy & MyGalaxy(Galaxy::GetGalaxy(n, 8, seed, true));
    System** MySystems = MyGalaxy.GetSystems(n);
    /*for (int i = 0; i < n; i++) {
            stringstream name;
            name << "System" << i;
            System & thisSystem(*(MySystems[i]));

            //Ogre::SceneNode* particleNode = mSceneMgr->getRootSceneNode()->crSieateChildSceneNode(name.str(),Ogre::Vector3(thisSystem.GetCenter().GetOrdinates(X),thisSystem.GetCenter().GetOrdinates(Y),thisSystem.GetCenter().GetOrdinates(Z)));
            Ogre::Entity* System = mSceneMgr->createEntity(name.str(), "sphere.mesh");
            name << "node";
            Ogre::SceneNode* SystemNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(name.str(), Ogre::Vector3(thisSystem.GetCenter().GetOrdinates(X), thisSystem.GetCenter().GetOrdinates(Y), thisSystem.GetCenter().GetOrdinates(Z)));
            SystemNode->attachObject(System);

            SystemNode->scale(0.001, 0.001, 0.001);
        }*/
    StellarObject** MyObjects = MySystems[0]->GetObjects(n);

    for (int i = 0; i < n; i++) {
        stringstream name;
        name << "Object" << i;
        StellarObject & thisObject(*(MyObjects[i]));

        //Ogre::SceneNode* particleNode = mSceneMgr->getRootSceneNode()->crSieateChildSceneNode(name.str(),Ogre::Vector3(thisSystem.GetCenter().GetOrdinates(X),thisSystem.GetCenter().GetOrdinates(Y),thisSystem.GetCenter().GetOrdinates(Z)));
        Ogre::Entity* System = mSceneMgr->createEntity(name.str(), "sphere.mesh");
        name << "node";
        Ogre::SceneNode* SystemNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(name.str(), Ogre::Vector3(thisObject.GetCenter()*500));
        SystemNode->attachObject(System);

        if (i == 0) {
            Ogre::ParticleSystem* sunParticle = mSceneMgr->createParticleSystem("Sun", "Space/Sun");
            Ogre::SceneNode* particleNode = SystemNode->createChildSceneNode("Particle");
            particleNode->attachObject(sunParticle);
        }

        SystemNode->scale(thisObject.GetRadius()*0.5, thisObject.GetRadius()*0.5, thisObject.GetRadius()*0.5);
    }


    //	Ogre::ManualObject* manual = mSceneMgr->createManualObject("manual");
    //	manual->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_POINT_LIST);

    Ogre::Light* light = mSceneMgr->createLight("MainLight");
    light->setPosition(20.0f, 80.0f, 50.0f);

}








#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

    int main(int argc, char *argv[]) {
        // Create application object
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



