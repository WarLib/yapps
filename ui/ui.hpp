#ifndef _UI_HPP
#define _UI_HPP

#include <RendererModules/Ogre/CEGUIOgreRenderer.h>
#include <CEGUI.h>
#include <string>
#include <vector>
#include "StellarObject.hpp"
#include "fpscounter.hpp"

#include "Input.h"
#include "ControllableObject.h"
#include "state.hpp"

namespace Yapps {
	class PosIndicator {
	protected:
		StellarObject* _target;
	public:
		PosIndicator(StellarObject* target);
		bool PosIndicator::ProjectPos(Ogre::Camera* cam,Ogre::Real& x,Ogre::Real& y);
		bool ProjectSizeAndPos(Ogre::Camera* cam, const Ogre::Real rad, Ogre::Real& x,Ogre::Real& y,Ogre::Real& cx,Ogre::Real& cy);
		bool operator==(Ogre::String name);

		PosIndicator& operator=(const PosIndicator&);

		Ogre::String& GetTargetName(void);
	};

	class Ui: public Listener {
		//members
	private:
	protected:
		CEGUI::OgreRenderer* mRenderer;

		CEGUI::System* mGUISystem;
	public:
		//methods
	protected:
		//global active UI
		static Ui* _ACT_UI;
		static Ui** _all_uis;
		static int _n_uis;

		int _id;
		std::string _name;

		Ogre::Camera* _camera;
		CEGUI::Window* MyRoot;

		virtual void SetActive(void) = 0;

		Ui(void);
	public:
		virtual void update(Ogre::Real time, const Ogre::Vector3& campos) = 0;
		void Init(Ogre::Camera* camera);
		virtual void Show() = 0;
		virtual void InjectKeyDown(const OIS::KeyEvent &arg) = 0;
		virtual void InjectKeyUp(const OIS::KeyEvent &arg) = 0;
		virtual ~Ui();

		static bool SwitchToUi(Ui* ui);
		static bool SwitchToUi(int id);
		static bool SwitchToUi(std::string name);
		static Ui* GetActiveUi(void);

		static void AddUi(Ui* new_ui);
	};

	class FlightUI: public Ui {
	private:
		static FlightUI* _instance;


		std::vector<PosIndicator> _targets;
		std::vector<CEGUI::Window*> _indicators;
		FlightUI();
		FlightUI(const FlightUI&);

        void dispatch(std::string msg);
	protected:
		void SetActive(void);
		CEGUI::Window* MyFps;
	public:
		void AddIndicator(StellarObject* Object);
		void DelIndicator(Ogre::String name);
		static FlightUI* getSingleton(void);
		void Show(void);
		void update(Ogre::Real time, const Ogre::Vector3& campos);
	
		void InjectKeyDown(const OIS::KeyEvent &arg);
		void InjectKeyUp(const OIS::KeyEvent &arg);

	};
};

#endif