#ifndef __yappsFunktor_h_
#define __yappsFunktor_h_

class yappsFunktor;
#include "yappsObject.h"

class yappsFunktor{

    yappsObject* parent;

public:
    yappsFunktor(yappsObject* parent){this->parent = parent;}
    void staticMovement();


};



#endif
