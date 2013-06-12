#include "physics.h"


using namespace Yapps;
  physicalEntity::physicalEntity(Vec3 position)
    {

        fallShape = new btBoxShape( btVector3(3,3,3) );
        fallMotionState =
            new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(position.x, position.y, position.z)));

        btScalar mass = 10;
        btVector3 fallInertia(0,0,0);
        fallShape->calculateLocalInertia(mass,fallInertia);
        btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,fallMotionState,fallShape,fallInertia);
        fallRigidBodyCI.m_restitution = 1.0;
        fallRigidBodyCI.m_friction = 0.9;


        myBody = new btRigidBody(fallRigidBodyCI);
    };
