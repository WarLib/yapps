#ifndef __yappsFunktor_h_
#define __yappsFunktor_h_
#include <iostream>

//declared in controllableObject
#include "Object.h"

namespace Yapps {
class Funktor {
    public:
        Object* parent;


        Funktor() {

            };
        void staticMovement();
        virtual void call() {
            staticMovement();
            };


    };




class mv_forward: public Funktor {
    public:
        mv_forward() {

            };
        void call() {
            std::cout<<"BLAAAAH"<< std::endl;
            };

    };


};
#endif
