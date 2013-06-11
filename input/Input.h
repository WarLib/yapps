#ifndef __yappsInput_h_
#define __yappsInput_h_

//Bruteforce importing

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

#include <string>
#include <map>
#include <list>
#include <sstream>
#include <iostream>
#include <fstream>

#define yappsMouse 1
#define yappsKeyboard 2

namespace Yapps {
class Listener {
    public:
        virtual void dispatch(std::string msg) {};

        virtual void notify(std::string msg) {
            dispatch(msg);
            };
        virtual void frame(Ogre::Real elapsed){
        };
    };


class Input {
    private:
        Yapps::Listener** Callbacks;
        int CallbacksLen;

        std::list<Listener*> frameListener;

        std::map<std::string, std::string> keybinds;


    public:
        static Yapps::Input*getInstance() {
            static Yapps::Input* instance = 0;
            if (!instance) {
                instance = new Yapps::Input();
                }
            return instance;
            }
        void subscribeKeys( Yapps::Listener* client ) {
            Callbacks[CallbacksLen] = client;
            CallbacksLen++;
            }
        void subscribeFrames( Yapps::Listener* client ) {
           frameListener.push_back(client);
            }
        void publishFrame( Ogre::Real Elapsed ){
            for(std::list<Listener*>::iterator iter = frameListener.begin(); iter != frameListener.end(); iter++)
                (*iter)->frame(Elapsed);


        }

        void publishKeys (std::string arg) {
            std::stringstream o;
            o << arg;
            std::cout << o.str() << std::endl;
            for (int i=0; i < CallbacksLen; i++)
                Callbacks[i]->notify( keybinds[ o.str() ]);
            }
        void setKeyBind(std::string key, std::string value) {
            keybinds.insert (
                std::pair<std::string, std::string>(key, value )
            );
            }
    private:
        Input() {
            CallbacksLen = 0;
            Callbacks = new Yapps::Listener*[32];

            /* Move this area to a configfile */
            loadConfig();/*
        setKeyBind("w", "forward");
        setKeyBind("s", "backward");
        setKeyBind("a", "left");*/
            setKeyBind("d", "right");
            saveConfig(); // OFC THIS IS DEBUGGING ONLY
            }
        void loadConfig();
        void saveConfig();


    protected:


    };

};

#endif
