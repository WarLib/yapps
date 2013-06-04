#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif


#include "MainApp.hpp"

MainApp::MainApp() {}
MainApp::~MainApp(){     }
void MainApp::createScene(void)
{
	int n = 1000;
	string seed = "magicrootseed";

	Galaxy & MyGalaxy(Galaxy::GetGalaxy(n, 8, seed, true));
	System** MySystems = MyGalaxy.GetSystems(n);

	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
	//	Ogre::ManualObject* manual = mSceneMgr->createManualObject("manual");
	//	manual->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_POINT_LIST);
	for (int i = 0; i < n; i++) {
		std::stringstream name;
		name << "System" << i;
		System & thisSystem(*(MySystems[i]));

		//Ogre::SceneNode* particleNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(name.str(),Ogre::Vector3(thisSystem.GetCenter().GetOrdinates(X),thisSystem.GetCenter().GetOrdinates(Y),thisSystem.GetCenter().GetOrdinates(Z)));
		Ogre::Entity* System = mSceneMgr->createEntity(name.str(), "sphere.mesh");
		name << "node";
		Ogre::SceneNode* SystemNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(name.str(), Ogre::Vector3(thisSystem.GetCenter().GetOrdinates(X), thisSystem.GetCenter().GetOrdinates(Y), thisSystem.GetCenter().GetOrdinates(Z)));
		SystemNode->attachObject(System);

		SystemNode->scale(0.001, 0.001, 0.001);
	}

	Ogre::Light* light = mSceneMgr->createLight("MainLight");
	light->setPosition(20.0f, 80.0f, 50.0f);


	// Main character
	Player *ogre = new Player("Player 1", mSceneMgr);
	ExtendedCamera *exCamera = new ExtendedCamera("Extended Camera", mSceneMgr, mCamera);

	// Frame listener to manage both character and camera updating and different camera modes
	// Need to create it here as we want to change some parameters here, thus avoiding defining 
	// ogre and exCamera as member variables
	mFrameListener = new SampleListener(mWindow, mCamera);
	static_cast<SampleListener *> (mFrameListener)->setCharacter(ogre);
	static_cast<SampleListener *> (mFrameListener)->setExtendedCamera(exCamera);

}
void MainApp::destroyScene(void)
{
}
void MainApp::createFrameListener(void)
{
	// This is where we instantiate our own frame listener
	//        mFrameListener= new SampleListener(mWindow, mCamera);
	mRoot->addFrameListener(mFrameListener);
}
 int main(int argc, char **argv)
 {
	 // Create application object
	 MainApp app;

	 try {
		 app.go();
	 } catch( Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32 
		 MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK |      MB_ICONERROR | MB_TASKMODAL);
#else
		 fprintf(stderr, "An exception has occured: %s\n",
			 e.getFullDescription().c_str());
#endif
	 }

	 return 0;
 }