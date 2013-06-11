#ifndef __yappsInertia_h_
#define __yappsInertia_h_
#include <iostream>

#include <OgreMath.h>

namespace Yapps
{
class Inertia
{
public:
    Ogre::Degree vector[3];

    Inertia()
    {
        vector[0] = 0;
        vector[1] = 0;
        vector[2] = 0;
    };

};
};
#endif
