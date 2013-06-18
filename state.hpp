#ifndef _STATE_HPP
#define _STATE_HPP

#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreViewport.h>
#include <OgreRenderWindow.h>
#include <OgreLogmanager.h>

#define CAMERA_NAME "YappsCam"

using namespace Ogre;

namespace Yapps {

	enum GameMode{IN_GAME,IN_INTRO,MAIN_MENU};

	class Scene {
	protected:
		SceneManager* _scMgr;
		Viewport* _vport;

		bool _createdScene;
	public:
		Scene(SceneManager* scMgr);
		//No destructor neccessary, deleting mRoot in yappsWindows clears it all - at least they said so

		operator SceneManager*();

		void activate(RenderWindow* rndWnd);
		void suspend(void);

		void CreateScene(void);
	};

	class GameState {
	private:

		static GameState STATE;
		GameState();
		GameState(const GameState& vgl);

		Root *mRoot;
		RenderWindow* _RenderWindow;

		Scene* _mainMenu;
		Scene* _inGame;
		Scene* _intro;

		Scene* ACTIVE;
	public:

		~GameState();

		void InjectRoot(Root* root, RenderWindow* rndWindow);

		static GameState& getSingleton(void);
		static GameState* getSingletonPtr(void);

		void SwitchScene(GameMode mode);
		Scene* GetActiveScene(void);
		Scene* GetScene(GameMode mode);
	};
};

#endif