
#include "Object.h"


using namespace Yapps;
Object::Object(Ogre::SceneManager* mSceneMgr,OgreBulletDynamics::DynamicsWorld* world, std::string name, std::string type, Vec3 pos){
    std::cout << "BUILDING OBJECT"<< std::endl;
        this->mSceneMgr = mSceneMgr;
        std::string endungMesh = ".mesh";
        std::string myMesh = type+endungMesh;
            std::cout << "LOADING OBJECT"<< std::endl;
        mEntity = mSceneMgr->createEntity(name.c_str(), myMesh.c_str());
        mEntity->setMaterialName("Examples/Rocky");

            std::cout << "LOADING OBJECT DONE"<< std::endl;
        mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(name, position ); //+Position!
        mMainNode->attachObject(mEntity);
    std::cout << "ATTACHED OBJECT"<< std::endl;





//        Ogre::SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
//    node->attachObject(entity);
//    node->scale(0.05f, 0.05f, 0.05f);   // the cube is too big for us
//    size *= 0.05f;                  // don't forget to scale down the Bullet-box too


    //    entity->setCastShadows(true);
    //Ogre::Entity *entity = mSceneMgr->createEntity(
     //                          "Box" + Ogre::StringConverter::toString(9),
     //                          "cube.mesh");



        Funktor* testmouse = new test_mouseturn();
        testmouse->setParent(this);
        abilities.push_back(testmouse);
        bind("mousex",testmouse);
        Funktor* testmousey = new test_mouseyaw();
        testmousey->setParent(this);
        abilities.push_back(testmousey);
        bind("mousey",testmousey);

        Funktor* rotDown = new trn_pitch_d();
        rotDown->setParent(this);
        abilities.push_back(rotDown);
        bind("down",rotDown);

        Funktor* rotUp = new trn_pitch_u();
        rotUp->setParent(this);
        abilities.push_back(rotUp);
        bind("up",rotUp);

        Funktor* rotLeft = new trn_yaw_l();
        rotLeft->setParent(this);
        abilities.push_back(rotLeft);
        bind("left",rotLeft);

        Funktor* rotRight = new trn_yaw_r();
        rotRight->setParent(this);
        abilities.push_back(rotRight);
        bind("right",rotRight);

        Funktor* fwd = new mv_accelerate();
        fwd->setParent(this);
        abilities.push_back(fwd);
        bind("accelerate",fwd);


        Funktor* rotlis = new rot_inertialistener();
        rotlis->setParent(this);
        abilities.push_back(rotlis);

        Funktor* mvlis = new mv_inertialistener();
        mvlis->setParent(this);
        abilities.push_back(mvlis);

        tellMeAboutFrames.push_back(mvlis);
        tellMeAboutFrames.push_back(rotlis);

        position = pos;




  mMainNode->scale(0.06,0.06,0.06);
  mMainNode->scale(rand()%100 /100.0,rand()%100 /100.0,rand()%100 /100.0);
         mMainNode->setPosition(pos);
             std::cout << "PHYSICAL OBJECT"<< std::endl;
physicalMe = new physicalEntity(name, position, mMainNode, mEntity, world);
mEntity->setCastShadows(true);

    std::cout << "BUILDING OBJECT DONE"<< std::endl;
}


Ogre::SceneNode *Object::getSightNode() {
    return mSightNode;
}

Ogre::SceneNode *Object::getCameraNode() {
    return mCameraNode;
}

Ogre::Vector3 Object::getWorldPosition() {
    return mMainNode->_getDerivedPosition();
}



void Object::frame(Ogre::Real elapsed){

    //std::cout << position << std::endl;
for (std::list<Funktor*>::iterator iter = tellMeAboutFrames.begin(); iter != tellMeAboutFrames.end(); ++iter)
    (*iter)->frame(elapsed);

return ;
 }
