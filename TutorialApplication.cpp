/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
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
#include "TutorialApplication.h"
#include "environment/world.hpp"
#include <sstream>

//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
}
//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void){
	int n = 1000;
	string seed = "magicrootseed";

	Galaxy & MyGalaxy(Galaxy::GetGalaxy(n, 8,seed,true));
	System** MySystems = MyGalaxy.GetSystems(n);

	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
	//	Ogre::ManualObject* manual = mSceneMgr->createManualObject("manual");
	//	manual->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_POINT_LIST);
	for (int i = 0; i < n; i++) {
		stringstream name;
		name << "System" << i;
		System& thisSystem(*(MySystems[i]));

		//Ogre::SceneNode* particleNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(name.str(),Ogre::Vector3(thisSystem.GetCenter().GetOrdinates(X),thisSystem.GetCenter().GetOrdinates(Y),thisSystem.GetCenter().GetOrdinates(Z)));
		Ogre::Entity* System = mSceneMgr->createEntity( name.str(), "sphere.mesh" );
		name << "node" ;
		Ogre::SceneNode* SystemNode = mSceneMgr->getRootSceneNode()->createChildSceneNode( name.str(), Ogre::Vector3(thisSystem.GetCenter().GetOrdinates(X),thisSystem.GetCenter().GetOrdinates(Y),thisSystem.GetCenter().GetOrdinates(Z)));
		SystemNode->attachObject( System);

		SystemNode->scale( 0.001, 0.001, 0.001 );
	}

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

	int main(int argc, char *argv[])
	{
		// Create application object
		TutorialApplication app;
		try {
			app.go();
		} catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
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
