#ifndef __yapps_physics_h_
#define __yapps_physics_h_


#include <iostream>
#include <cmath>

#include <sstream>
#include <string>


#include <btBulletDynamicsCommon.h>

#include "OgreBulletDynamics.h"
#include "OgreBulletDynamicsRigidBody.h"				 // for OgreBullet
#include "Shapes/OgreBulletCollisionsTrimeshShape.h"
#include "Shapes/OgreBulletCollisionsStaticPlaneShape.h" // for static planes
#include "Shapes/OgreBulletCollisionsBoxShape.h"
#include "Shapes/OgreBulletCollisionsSphereShape.h"
#include "Shapes/OgreBulletCollisionsCompoundShape.h"


#include <Utils/OgreBulletCollisionsMeshToShapeConverter.h>
#include <list>

#include <OgreQuaternion.h>
#include <OgreEntity.h>

#include <fstream>

namespace Yapps
{

class physicsUniverse;

}

#include "../environment/ordinates.hpp"
namespace Yapps
{



class physicalEntity: public OgreBulletCollisions::StaticMeshToShapeConverter
{
public:
OgreBulletDynamics::RigidBody * myChassis;
    float mass;
     std::string name;
    OgreBulletCollisions::CompoundCollisionShape* compound;
    Ogre::SceneNode* node;
    OgreBulletDynamics::DynamicsWorld*world;

    void applyOgreShape(Ogre::Entity *entity);
    void rebuild();

    physicalEntity( std::string name,Vec3 pos,Ogre::SceneNode* node,  Ogre::Entity* entity, OgreBulletDynamics::DynamicsWorld*world);



};

class physicsUniverse
{
public:
    OgreBulletDynamics::DynamicsWorld* dynamicsWorld;
    btRigidBody* groundRigidBody;

    btCollisionShape* groundShape;

    physicsUniverse(Ogre::SceneManager* mSceneMgr);

    ~physicsUniverse()
    {

    };
};
};

#endif

