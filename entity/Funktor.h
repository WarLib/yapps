#ifndef __yappsFunktor_h_
#define __yappsFunktor_h_
namespace Yapps {
class Funktor;
};
#include "Object.h"

namespace Yapps {
class Funktor{

    Yapps::Object* parent;

public:
    Funktor(Yapps::Object* parent){this->parent = parent;}
    void staticMovement();


};

};

#endif
