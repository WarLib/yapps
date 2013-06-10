#ifndef __yappsControllableObject_h_
#define __yappsControllableObject_h_

namespace Yapps{
class ControllableObject;
class Funktor;
};

#include "../input/Input.h"

#include <map>


namespace Yapps {
class ControllableObject:public Listener {
    private:
        std::map<std::string, Funktor*> bindings;

    public:
        // Eine methode für jede funktion die ein steuerbares Objekt haben kann //

        virtual void dispatch(std::string msg);

        bool bind(std::string msg, Funktor* callback) {
            try {
                if (!bindings[msg]) {
                    bindings[msg] = callback;
                    return true;
                    }
                return false;
                }
            catch(...) {}
            return false;
            };




    };

};

#include "Funktor.h"

#endif
