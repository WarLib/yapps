#ifndef __yappsFunktor_h_
#define __yappsFunktor_h_
#include <iostream>
#include <OgreMath.h>

//declared in controllableObject
#include "Object.h"

namespace Yapps {
class Funktor {
    public:
        Object* parent;

        virtual void setParent ( Object * p){parent = p;};
        virtual void call() {};
        virtual void frame(Ogre::Real elapsed){};


    };




class trn_pitch_d: public Funktor {
    public:

        void call();
    };
class trn_pitch_u: public Funktor {
    public:

        void call();
    };
class trn_yaw_l: public Funktor {
    public:

        void call();
    };
class trn_yaw_r: public Funktor {
    public:

        void call();
    };





class rot_inertialistener: public Funktor {
    public:

        void frame(Ogre::Real elapsed); // <--- doesnt really take elapsed atm
    };
};


#endif
