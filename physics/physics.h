#ifndef __yapps_physics_h_
#define __yapps_physics_h_


#include <iostream>

#include <btBulletDynamicsCommon.h>
#include <list>

#include <OgreQuaternion.h>
#include <OgreEntity.h>

#include <fstream>
#include "../environment/ordinates.hpp"
namespace Yapps
{

class physicalEntity
{
public:
    btCollisionShape* fallShape;
    btDefaultMotionState* fallMotionState ;
    btRigidBody* myBody;

    void applyOgreShape(Ogre::Entity *entity);

    physicalEntity(Vec3 position);
    Vec3 toYVec3(){

    btTransform trans;
    myBody->getMotionState()->getWorldTransform(trans);
    return Vec3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ() );
    }
    Ogre::Quaternion toQuat(){
        btQuaternion orientation = myBody->getOrientation();
    return Ogre::Quaternion( orientation.getX(),orientation.getY(),orientation.getZ() ,orientation.getW() );
    }


};

class physicsUniverse
{
public:
    btBroadphaseInterface*broadphase;
    btDefaultCollisionConfiguration*collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver*solver;
    btDiscreteDynamicsWorld*dynamicsWorld;
    btRigidBody* groundRigidBody;

    btCollisionShape* groundShape;

    physicsUniverse()
    {
        broadphase = new btDbvtBroadphase();

        collisionConfiguration = new btDefaultCollisionConfiguration();
        dispatcher = new btCollisionDispatcher(collisionConfiguration);

        solver = new btSequentialImpulseConstraintSolver;

        dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);

        dynamicsWorld->setGravity(btVector3(0,-50,0));


        groundShape = new btStaticPlaneShape(btVector3(0,1,0),1);
///////////////////////
        btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
        btRigidBody::btRigidBodyConstructionInfo
        groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
        groundRigidBody = new btRigidBody(groundRigidBodyCI);
        dynamicsWorld->addRigidBody(groundRigidBody);


    }
    ~physicsUniverse()
    {

        dynamicsWorld->removeRigidBody(groundRigidBody);
        delete groundRigidBody->getMotionState();
        delete groundRigidBody;


        delete groundShape;


        delete dynamicsWorld;
        delete solver;
        delete collisionConfiguration;
        delete dispatcher;
        delete broadphase;
    };
};
};

#endif

