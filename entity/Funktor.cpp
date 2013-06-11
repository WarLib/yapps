#include "Funktor.h"

using namespace Yapps;


        void trn_pitch_d::call() {
            std::cout<<"BLAAAAH"<< std::endl;
            std::cout << parent->mMainNode->getPosition() << std::endl;

            parent->Rotation.vector[1] += Ogre::Radian(0.01);
            };


        void trn_pitch_u::call() {
            std::cout<<"BLAAAAH"<< std::endl;
            std::cout << parent->mMainNode->getPosition() << std::endl;

            parent->Rotation.vector[1] -=  Ogre::Radian(0.01);
            };

        void trn_yaw_l::call() {
            std::cout<<"BLAAAAH"<< std::endl;
            std::cout << parent->mMainNode->getPosition() << std::endl;

            parent->Rotation.vector[0] += Ogre::Radian(0.01);
            };


        void trn_yaw_r::call() {
            std::cout<<"BLAAAAH"<< std::endl;
            std::cout << parent->mMainNode->getPosition() << std::endl;

            parent->Rotation.vector[0] -= Ogre::Radian(0.01);
            };





        void rot_inertialistener::frame(Ogre::Real elapsed){
            std::cout << "pitching"<< std::endl;
            parent->mMainNode->pitch( parent->Rotation.vector[1] );
            parent->mMainNode->yaw( parent->Rotation.vector[0] );
        };
