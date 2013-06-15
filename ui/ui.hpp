#ifndef _UI_HPP
#define _UI_HPP

#include <RendererModules/Ogre/CEGUIOgreRenderer.h>
#include <CEGUI.h>
#include <string>
#include <vector>
#include "StellarObject.hpp"

namespace Yapps {

	class PosIndicator {
	public:
		StellarObject& _target;
		PosIndicator(StellarObject& target);
		bool PosIndicator::ProjectPos(Ogre::Camera* cam,Ogre::Real& x,Ogre::Real& y);
		bool ProjectSizeAndPos(Ogre::Camera* cam, const Ogre::Real rad, Ogre::Real& x,Ogre::Real& y,Ogre::Real& cx,Ogre::Real& cy);
	};

	class Ui {
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
		virtual void SetActive(void) = 0;

		Ui(void);
	public:
		virtual void update(Ogre::Real time) = 0;
		void Init(Ogre::Camera* camera);
		virtual void Show() = 0;
		virtual void InjectKeyDown() = 0;
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
	protected:
		void SetActive(void);
	public:
		void AddIndicator(StellarObject& Object);
		static FlightUI* getSingleton(void);
		void Show(void);
		void update(Ogre::Real time);
	
		void InjectKeyDown();
	};
};

#endif