#ifndef __yappsFunktor_h_
#define __yappsFunktor_h_
#include <iostream>
#include <OgreMath.h>



//declared in controllableObject
#include "Object.h"
#include "../environment/ordinates.hpp"

namespace Yapps {
class Funktor {
    public:
        Object* parent;

        virtual void setParent ( Object * p){parent = p;};
        virtual void call(int argc=0, void* argv=NULL) {};
        virtual void frame(Ogre::Real elapsed){};


    };




class trn_pitch_d: public Funktor {
    public:
        void call(int argc=0, void* argv=NULL);
    };
class test_mouseturn: public Funktor{
public:
    void call(int argc=0, void* argv=NULL);
};
class test_mouseyaw: public Funktor{
public:
    void call(int argc=0, void* argv=NULL);
};

class trn_pitch_u: public Funktor {
    public:
        void call(int argc=0, void* argv=NULL);
    };
class trn_yaw_l: public Funktor {
    public:
        void call(int argc=0, void* argv=NULL);
    };
class trn_yaw_r: public Funktor {
    public:
        void call(int argc=0, void* argv=NULL);
    };

class mv_accelerate: public Funktor {
    public:
        void call(int argc=0, void* argv=NULL);
    };


class rot_inertialistener: public Funktor {
    public:
        void frame(Ogre::Real elapsed); // <--- doesnt really take elapsed atm
    };
class mv_inertialistener: public Funktor {
    public:
        void frame(Ogre::Real elapsed); // <--- doesnt really take elapsed atm
    };
};


#endif
