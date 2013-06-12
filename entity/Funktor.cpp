#include "Funktor.h"

using namespace Yapps;


        void trn_pitch_d::call() {
            std::cout << parent->mMainNode->getPosition() << std::endl;
            parent->Rotation += Vec3(1,0,0);

            };


        void trn_pitch_u::call() {
            std::cout << parent->mMainNode->getPosition() << std::endl;


            };

        void trn_yaw_l::call() {
            std::cout << parent->mMainNode->getPosition() << std::endl;


            };


        void trn_yaw_r::call() {

            std::cout << parent->mMainNode->getPosition() << std::endl;


            };


        void mv_accelerate::call() {
            std::cout << parent->mMainNode->getPosition() << std::endl;
            std::cout <<"----"<<std::endl;
            parent->physicalMe->myBody->applyImpulse( btVector3(0,0,10), btVector3(0,0,0) );
            };




        void rot_inertialistener::frame(Ogre::Real elapsed){
            //std::cout << "a"<< std::endl;

        };

        void mv_inertialistener::frame(Ogre::Real elapsed){
            //std::cout << "b"<< std::endl;


        };
