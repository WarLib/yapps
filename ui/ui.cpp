#include "ui.hpp"
#include <OISMouse.h>
#include <iostream>
#include <sstream>
#include <OgreCamera.h>

using namespace std;
using namespace Yapps;
//OnScreen Position Indicator
PosIndicator::PosIndicator(StellarObject& target): _target(target) {};

bool PosIndicator::ProjectPos(Ogre::Camera* cam,Ogre::Real& x,Ogre::Real& y) {
	Ogre::Vector3 eyeSpacePos = cam->getViewMatrix(true) * _target.GetCenter();
	// z < 0 means in front of cam
	if (eyeSpacePos.z < 0) {
		// calculate projected pos
		Ogre::Vector3 screenSpacePos = cam->getProjectionMatrix() * eyeSpacePos;
		x = screenSpacePos.x;
		y = screenSpacePos.y;
		return true;
	} else {
		x = (-eyeSpacePos.x > 0) ? -1 : 1;
		y = (-eyeSpacePos.y > 0) ? -1 : 1;
		return false;
	}
}

bool    PosIndicator::ProjectSizeAndPos(Ogre::Camera* cam, const Ogre::Real rad, Ogre::Real& x,Ogre::Real& y,Ogre::Real& cx,Ogre::Real& cy) {
	Ogre::Vector3 eyeSpacePos = cam->getViewMatrix(true) * _target.GetCenter();
	// z < 0 means in front of cam
	if (eyeSpacePos.z < 0) {
		// calculate projected pos
		Ogre::Vector3 screenSpacePos = cam->getProjectionMatrix() * eyeSpacePos;
		x = screenSpacePos.x;
		y = screenSpacePos.y;
		// calculate projected size
		Ogre::Vector3 spheresize(rad, rad, eyeSpacePos.z);
		spheresize = cam->getProjectionMatrix() * spheresize;
		cx = spheresize.x;
		cy = spheresize.y;
		return true;
	} else {
		cx = 0;
		cy = 0;
		x = (-eyeSpacePos.x > 0) ? -1 : 1;
		y = (-eyeSpacePos.y > 0) ? -1 : 1;
		return false;
	}
}
//
CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID)
{
	switch (buttonID)
	{
	case OIS::MB_Left:
		return CEGUI::LeftButton;

	case OIS::MB_Right:
		return CEGUI::RightButton;

	case OIS::MB_Middle:
		return CEGUI::MiddleButton;

	default:
		return CEGUI::LeftButton;
	}
}


//BASE CLASS AND STATICS

Ui* Ui::_ACT_UI = 0;
Ui** Ui::_all_uis = 0;
int Ui::_n_uis = 0;

Ui::Ui(void) {
}

Ui::~Ui() {
}

bool Ui::SwitchToUi(Ui* ui) {
	bool found = false;
	for (int i = 0; i < _n_uis; i++) {
		if (ui == _all_uis[i])
			found = true;
	}
	if (! found) {
		AddUi(ui);
	}
	_ACT_UI = ui;
	_ACT_UI->SetActive();
	return found;
}

bool Ui::SwitchToUi(int id) {
	bool found = false;
	for (int i = 0; i < _n_uis; i++) {
		if (_all_uis[i]->_id == id) {
			_ACT_UI = _all_uis[i];
			_ACT_UI->SetActive();
			found = true;
			break;
		}
	}
	return found;
}

bool Ui::SwitchToUi(std::string name) {
	bool found = false;
	for (int i = 0; i < _n_uis; i++) {
		if (name.compare(_all_uis[i]->_name) == 0) {
			_ACT_UI = _all_uis[i];
			_ACT_UI->SetActive();
			found = true;
			break;
		}
	}
	return found;
}


Ui* Ui::GetActiveUi(void) {
	return _ACT_UI;
}

void Ui::AddUi(Ui* new_ui) {
	int tmp, new_size;
	Ui** new_uis = 0;
	tmp = _n_uis + 1;
	new_size = 1;

	while (new_size <= tmp) {
		new_size *= 2;
	}

	new_uis = new Ui*[new_size];
	for (int i = 0; i < _n_uis; i++) {
		new_uis[i] = _all_uis[i];
	}
	new_uis[_n_uis] = new_ui;

	delete[] _all_uis;
	_all_uis = new_uis;
	_n_uis = tmp;
	_ACT_UI = new_ui;
}


void Ui::Init(Ogre::Camera* camera) {
	_camera = camera;
	mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();
	mGUISystem = CEGUI::System::getSingletonPtr();

	CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
	CEGUI::ImagesetManager::getSingleton().create("Yapps.imageset");


	try {
		CEGUI::SchemeManager::getSingleton().create("Yapps.scheme");
	} catch (CEGUI::GenericException e) {
		cout << "SCHEME_LOADING_ERROR" << endl;
		cout << e.getFileName() << endl;
		cout << e.getMessage() << endl;
		cout << e.getName() << endl;
		cout << e.getLine() << endl;
		exit(1);
	}

	//mGUISystem->setDefaultMouseCursor("TaharezLook", "MouseArrow");
}


//INGAME FLIGHT
FlightUI* FlightUI::_instance = 0;

FlightUI::FlightUI():Ui() {};

FlightUI* FlightUI::getSingleton(void) {
	if (_instance == 0) {
		_instance = new FlightUI();
		AddUi(_instance);
	}
	return _instance;
}

void FlightUI::SetActive(void) {
}

void FlightUI::Show(void) {

	mGUISystem = CEGUI::System::getSingletonPtr();
	CEGUI::WindowManager* Wmgr = CEGUI::WindowManager::getSingletonPtr();

	try {
		CEGUI::Window* MyRoot;
		MyRoot = Wmgr->createWindow("DefaultWindow","ROOT");
		for (int i = 0; i < _targets.size(); i++) {
			stringstream name;
			name << "Indicator" << i;
			_indicators.push_back(Wmgr->createWindow("Yapps/StaticImage",name.str()));
			_indicators[i]->setProperty("Image", "set:Yapps/Main image:Lock");
			MyRoot->addChildWindow(_indicators[i]);
			//_indicators[i]->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.0f, 0.0f ), CEGUI::UDim( 0.0f, 0.0f) ) );
			//_indicators[i]->setSize( CEGUI::UVector2( CEGUI::UDim( 0.1f, 0.0f ), CEGUI::UDim( 0.1f, 0.0f ) ) );
		}

		mGUISystem->setGUISheet(MyRoot);

	} catch (CEGUI::GenericException e) {
		cout << "LAYOUT_LOADING_ERROR" << endl;
		cout << e.getFileName() << endl;
		cout << e.getMessage() << endl;
		cout << e.getName() << endl;
		cout << e.getLine() << endl;
	} catch (CEGUI::UnknownObjectException e) {
		cout << "LAYOUT_LOADING_ERROR" << endl;
		cout << e.getFileName() << endl;
		cout << e.getMessage() << endl;
		cout << e.getName() << endl;
		cout << e.getLine() << endl;
	} catch (...) {
		cout << "UNKNOWN ERROR!!" << endl;
	}
}

void FlightUI::InjectKeyDown() {
}

void FlightUI::AddIndicator(StellarObject& Object) {
	_targets.push_back(PosIndicator(Object));
}

void FlightUI::update(Ogre::Real time) {
	for (int i = 0; i < _targets.size(); i++) {
		Ogre::Real tmp_x, tmp_y;
		Ogre::Real size_x,size_y,relative;
		bool visible;
		_targets[i].ProjectSizeAndPos(_camera,100,tmp_x,tmp_y,size_x,size_y);
		visible = (tmp_x > -1 && tmp_x < 1 && tmp_y > -1 && tmp_y < 1);
		if (visible) {
			relative = size_x / size_y;
			if (tmp_x < -1) {
				tmp_x = 0;
			} else if (tmp_x > 1) {
				tmp_x = 1;
			} else {
				tmp_x = (tmp_x + 1) / 2.0;
			}

			if (tmp_y < -1) {
				tmp_y = 1;
			} else if (tmp_y > 1) {
				tmp_y = 0;
			} else {
				tmp_y = (-tmp_y + 1)/ 2.0;
			}
			size_x *= 1000;
			if (size_x < 30) {
				size_x = 30;
			}
			if (size_x > 100) {
				size_x = 100;
			}
			size_y = size_x / relative;
			_indicators[i]->setPosition(CEGUI::UVector2( CEGUI::UDim(tmp_x -0.05f * size_x / 100  , 0.0f ), CEGUI::UDim(tmp_y -0.05f * size_y / 100 , 0.0f) ) );
			_indicators[i]->setSize( CEGUI::UVector2( CEGUI::UDim( 0.1f * size_x / 100 , 0.0f ), CEGUI::UDim( 0.1f * size_y / 100 , 0.0f ) ) );
		}
		_indicators[i]->setVisible(visible);
	}
}