#include "physics.h"


using namespace Yapps;
physicalEntity::physicalEntity( std::string name,Vec3 pos,Ogre::SceneNode* node,  Ogre::Entity* entity, OgreBulletDynamics::DynamicsWorld*world)
{
    this->node = node;
    this->world = world;
    this->name = name;
    Ogre::Vector3 size = Ogre::Vector3::ZERO;   // size of the box
    // starting position of the box
    Ogre::Vector3 position = (pos);
    Ogre::AxisAlignedBox boundingB = entity->getBoundingBox();
    size = boundingB.getMaximum();
    size /= 32.0f;


    static int itemcount = 0;
    mass = 10;

           Ogre::Vector3 chassisShift(0, 0, 0);
    // create an ordinary, Ogre mesh with texture

    Ogre::Quaternion rotation (0,0,0,1);

    //OgreBulletCollisions::StaticMeshToShapeConverter *trimeshConverter = new StaticMeshToShapeConverter( entity );

    //OgreBulletCollisions::TriangleMeshCollisionShape *sceneTriMeshShape = trimeshConverter->createTrimesh();
//OgreBulletCollisions::TriangleMeshCollisionShape* trimesh = trimeshConverter->createTrimesh();
// OgreBulletCollisions::ConvexHullCollisionShape* sceneTriMeshShape = trimeshConverter->createConvex();
    //delete trimeshConverter;
//    OgreBulletCollisions::SphereCollisionShape* chassisShape = new OgreBulletCollisions::SphereCollisionShape( sqrt(size[0]*size[0]+size[1]*size[1] +size[2]*size[2] ) );
    OgreBulletCollisions::BoxCollisionShape* chassisShape = new OgreBulletCollisions::BoxCollisionShape( size );

    compound = new OgreBulletCollisions::CompoundCollisionShape();
    compound -> addChildShape ( chassisShape, chassisShift );

    myChassis = new OgreBulletDynamics::RigidBody(name, world);

    myChassis->setShape(node, compound, 0.3, 0.3, mass,position, Ogre::Quaternion::IDENTITY);

    myChassis->enableActiveState();

    myChassis->disableDeactivation ();

    myChassis->setDamping(0.5,0.5);
};

void physicalEntity::rebuild()
{
std::cout << "Rebuild!"<< std::endl;
    Ogre::Vector3 position = myChassis->getCenterOfMassPosition();
    Ogre::Quaternion rotation = myChassis->getCenterOfMassOrientation();
    delete myChassis;

    myChassis = new OgreBulletDynamics::RigidBody(name, world);

    myChassis->setShape(node, compound, 0.3, 0.3, mass,position, rotation);

    myChassis->enableActiveState();

    myChassis->disableDeactivation ();

    myChassis->setDamping(0.01,0.01);

}



physicsUniverse::physicsUniverse(Ogre::SceneManager* mSceneMgr)
{

    dynamicsWorld = new OgreBulletDynamics::DynamicsWorld(mSceneMgr,  // gravity vector for Bullet
            Ogre::AxisAlignedBox (-10000, -10000, -10000,10000, 10000, 10000),
            Ogre::Vector3(0,-1,0) );

    Ogre::Entity *ent;
    Ogre::Plane p;
    p.normal = Ogre::Vector3(0,1,0);
    p.d = 0;
    Ogre::MeshManager::getSingleton().createPlane(
        "FloorPlane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        p, 200000, 200000, 20, 20, true, 1, 9000, 9000, Ogre::Vector3::UNIT_Z);
    // Create an entity (the floor)
    ent = mSceneMgr->createEntity("floor", "FloorPlane");
    ent->setMaterialName("Examples/Rocky");
    ent->setCastShadows(false);
    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);

    OgreBulletCollisions::CollisionShape *Shape;
    Shape = new OgreBulletCollisions::StaticPlaneCollisionShape(Ogre::Vector3(0,1,0), 0); // (normal vector, distance)
    OgreBulletDynamics::RigidBody *defaultPlaneBody = new OgreBulletDynamics::RigidBody(
        "BasePlane",
        dynamicsWorld);
    defaultPlaneBody->setStaticShape(Shape, 0.1, 0.8); // (shape, restitution, friction)
    // push the created objects to the deques
    OgreBulletCollisions::DebugDrawer *debugDrawer = new OgreBulletCollisions::DebugDrawer();
    dynamicsWorld->setDebugDrawer(debugDrawer);
    dynamicsWorld->setShowDebugShapes(true);
    Ogre::SceneNode *node =  mSceneMgr->getRootSceneNode()->createChildSceneNode("debugDrawer", Ogre::Vector3::ZERO);
    node->attachObject(static_cast <Ogre::SimpleRenderable *> (debugDrawer));

};



