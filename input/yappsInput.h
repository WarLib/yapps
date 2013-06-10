#ifndef __yappsInput_h_
#define __yappsInput_h_



#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <string>
#include <map>
#include <sstream>
#include <iostream>
#include <fstream>

#define yappsMouse 1
#define yappsKeyboard 2

class yappsListener{
public:
    virtual void dispatch(std::string msg){};

    virtual void notify(std::string msg){
    dispatch(msg);
    };
};


class yappsInput
{
private:
    yappsListener** Callbacks;
    int CallbacksLen;

    std::map<std::string, std::string> keybinds;


public:
    static yappsInput*getInstance()
    {
        static yappsInput* instance = 0;
        if (!instance)
        {
            instance = new yappsInput();
        }
        return instance;
    }
    void subscribe( yappsListener* client ){Callbacks[CallbacksLen] = client; CallbacksLen++; }
    void publish (std::string arg){
        std::stringstream o;
        o << arg;
        std::cout << o.str() << std::endl;
        for (int i=0; i < CallbacksLen; i++)
                        Callbacks[i]->notify( keybinds[ o.str() ]);
     }
    void setKeyBind(std::string key, std::string value){
    keybinds.insert (
                     std::pair<std::string, std::string>(key, value )
                     );
    }
private:
    yappsInput() {
        CallbacksLen = 0;
        Callbacks = new yappsListener*[32];

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



#endif
