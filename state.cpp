#include "state.hpp"

using namespace Yapps;

//-------------------------SCENES----------------------------------

Scene::Scene(SceneManager* scMgr) {
	_scMgr = scMgr;
	_scMgr->createCamera(CAMERA_NAME);
	_createdScene = false;
}

Scene::operator SceneManager*() {
	return _scMgr;
}

void Scene::activate(RenderWindow* rndWnd) {
    rndWnd->removeAllViewports();
 
    Ogre::Camera *cam = _scMgr->getCamera(CAMERA_NAME);
    Ogre::Viewport *vp = rndWnd->addViewport(cam);
 
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
    cam->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

	if (!_createdScene) {
		CreateScene();
	}
}

void Scene::suspend(void) {
}

void Scene::CreateScene(void) {
	_createdScene = true;
	LogManager::getSingleton().logMessage(Ogre::LML_NORMAL, "Creating Scene!");
}

//-------------------------GAMESTATE-------------------------------

GameState GameState::STATE;

GameState::GameState() {
	mRoot = 0;
	ACTIVE = 0;
	_inGame = 0;
	_intro = 0;
	_mainMenu = 0;
}

GameState::~GameState() {
	if (mRoot) {
		delete _inGame;
		delete _intro;
		delete _mainMenu;
	}
}

void GameState::InjectRoot(Ogre::Root* root, RenderWindow* rndWindow) {
	mRoot = root;
	_RenderWindow = rndWindow;
	_inGame = new Scene(mRoot->createSceneManager(Ogre::ST_GENERIC));
	_intro = new Scene(mRoot->createSceneManager(Ogre::ST_GENERIC));
	_mainMenu = new Scene(mRoot->createSceneManager(Ogre::ST_GENERIC));
}

GameState& GameState::getSingleton(void) {
	return STATE;
}

GameState* GameState::getSingletonPtr(void) {
	return &STATE;
}

void GameState::SwitchScene(GameMode mode) {
	switch (mode)  {
	case IN_GAME:
		if (ACTIVE != _inGame) {
			_intro->suspend();
			_mainMenu->suspend();
			_inGame->activate(_RenderWindow);
		}
		ACTIVE = _inGame;
		break;
	case IN_INTRO:
		if (ACTIVE != _intro) {
			_mainMenu->suspend();
			_inGame->suspend();
			_intro->activate(_RenderWindow);
		}
		ACTIVE = _intro;
		break;
	case MAIN_MENU:
		if (ACTIVE != _mainMenu) {
			_inGame->suspend();
			_intro->suspend();
			_mainMenu->activate(_RenderWindow);
		}
		ACTIVE = _mainMenu;
		break;
	default:
		ACTIVE = 0;
		break;
	}
}

Scene* GameState::GetActiveScene(void) {
	return ACTIVE;
}

Scene* GameState::GetScene(GameMode mode) {
	switch (mode) {
	case IN_GAME:
		return _inGame;
		break;
	case IN_INTRO:
		return _intro;
		break;
	case MAIN_MENU:
		return _mainMenu;
		break;
	default:
		return 0;
		break;
	}
}
