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
        virtual void call() {

            };


    };




class mv_forward: public Funktor {
    public:

        void call() ;

    };


};
#endif
