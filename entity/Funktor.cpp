#include "Funktor.h"

using namespace Yapps;


        void mv_forward::call() {
            std::cout<<"BLAAAAH"<< std::endl;
            std::cout << parent->mMainNode->getPosition() << std::endl;
            //Ogre::Quaternion oldRot = parent->mMainNode->getOrientation();

            //oldRot[2]+=1;

            //parent->mMainNode->setOrientation(oldRot);

            //std::cout << oldRot << std::endl;
            Ogre::Degree winkel;
            winkel = 1.0;
            parent->mMainNode->pitch(winkel);
            };
