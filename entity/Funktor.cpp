#include "Funktor.h"

using namespace Yapps;


        void trn_pitch_d::call(int argc, void* argv) {
            std::cout << parent->mMainNode->getPosition() << std::endl;
             parent->physicalMe->mass = 100;
            parent->physicalMe->rebuild();
            };


        void trn_pitch_u::call(int argc, void* argv) {
            std::cout << parent->mMainNode->getPosition() << std::endl;


            };

        void trn_yaw_l::call(int argc, void* argv) {
            std::cout << parent->mMainNode->getPosition() << std::endl;

    parent->physicalMe->myChassis->enableActiveState();
            parent->physicalMe->myChassis->applyImpulse(parent->physicalMe->myChassis->getCenterOfMassOrientation() *  Ogre::Vector3(  0.0005,0,0), parent->physicalMe->myChassis->getCenterOfMassOrientation() * Ogre::Vector3(0,0, 100000) );
            //parent->physicalMe->myChassis->applyImpulse( Ogre::Vector3( -0.0005,0,0), Ogre::Vector3(0,0,-100000) );
            //parent->physicalMe->myChassis->getBulletRigidBody()->applyTorqueImpulse( btVector3(0,10,0) );
            };


        void trn_yaw_r::call(int argc, void* argv) {

    parent->physicalMe->myChassis->enableActiveState();
            parent->physicalMe->myChassis->applyImpulse( Ogre::Vector3( -0.0005,0,0), Ogre::Vector3(0,0, 100000) );
            parent->physicalMe->myChassis->applyImpulse( Ogre::Vector3(  0.0005,0,0), Ogre::Vector3(0,0,-100000) );
            std::cout << parent->mMainNode->getPosition() << std::endl;


            };


        void mv_accelerate::call(int argc, void* argv) {
            std::cout << parent->mMainNode->getPosition() << std::endl;

            parent->physicalMe->myChassis->enableActiveState();
            std::cout <<"----"<<std::endl;
            parent->physicalMe->myChassis->applyImpulse(parent->physicalMe->myChassis->getCenterOfMassOrientation() * Ogre::Vector3(0,0,-400) , Ogre::Vector3(0,0,0) );
            //parent->physicalMe->myChassis->applyTorque( 65);
            //parent->physicalMe->myChassis->getBulletRigidBody()->applyAngularForce(btVector3(0.0f,0.5f,0.5f));
            std::cout <<"----"<<std::endl;
            };



        void test_mouseturn::call(int argc, void* argv){

        std::cout << argc << "--------------" <<std::endl;
            parent->physicalMe->myChassis->applyImpulse( parent->physicalMe->myChassis->getCenterOfMassOrientation()*Ogre::Vector3(  0.000001*argc,0,0), parent->physicalMe->myChassis->getCenterOfMassOrientation()*Ogre::Vector3(0,0,100000) );
            parent->physicalMe->myChassis->applyImpulse( parent->physicalMe->myChassis->getCenterOfMassOrientation()*Ogre::Vector3( -0.000001*argc,0,0), parent->physicalMe->myChassis->getCenterOfMassOrientation()*Ogre::Vector3(0,0,-100000) );
        };
        void test_mouseyaw::call(int argc, void* argv){

        std::cout << argc << "--------------" <<std::endl;
            parent->physicalMe->myChassis->applyImpulse( parent->physicalMe->myChassis->getCenterOfMassOrientation()*Ogre::Vector3( 0,0, 0.000001*argc), parent->physicalMe->myChassis->getCenterOfMassOrientation()*Ogre::Vector3(0, 100000,0) );
            parent->physicalMe->myChassis->applyImpulse( parent->physicalMe->myChassis->getCenterOfMassOrientation()*Ogre::Vector3( 0,0,-0.000001*argc), parent->physicalMe->myChassis->getCenterOfMassOrientation()*Ogre::Vector3(0,-100000,0) );
        };

        void rot_inertialistener::frame(Ogre::Real elapsed){
            //std::cout << "a"<< std::endl;

        };

        void mv_inertialistener::frame(Ogre::Real elapsed){
            //std::cout << "b"<< std::endl;


        };
