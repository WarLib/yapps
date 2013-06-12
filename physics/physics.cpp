#include "physics.h"


using namespace Yapps;
  physicalEntity::physicalEntity(Vec3 position)
    {
        static int height = 3;
        fallShape = new btSphereShape(3.0);
        fallMotionState =
            new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(position.x, position.y, position.z)));
        height +=3;

        btScalar mass = 1;
        btVector3 fallInertia(0,0,0);
        fallShape->calculateLocalInertia(mass,fallInertia);
        btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,fallMotionState,fallShape,fallInertia);

        myBody = new btRigidBody(fallRigidBodyCI);
    };
