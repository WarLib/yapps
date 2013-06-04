#include "player.hpp"
// Specialization of the Character class - Our dear Ogre :D

Player::Player(String name, SceneManager *sceneMgr) {
    // Setup basic member references
    mName = name;
    mSceneMgr = sceneMgr;

    // Setup basic node structure to handle 3rd person cameras
    mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName,Vector3(0,0,-1000));
    mSightNode = mMainNode->createChildSceneNode(mName + "_sight", Vector3(0, 0, 0));
    mCameraNode = mMainNode->createChildSceneNode(mName + "_camera", Vector3(0, 50, -1200));

    // Give this character a shape :)
    mEntity = mSceneMgr->createEntity(mName, "fighter.mesh");
    mMainNode->attachObject(mEntity);
}

Player::~Player() {
    mMainNode->detachAllObjects();
    delete mEntity;
    mMainNode->removeAndDestroyAllChildren();
    mSceneMgr->destroySceneNode(mName);
}

void Player::update(Real elapsedTime, OIS::Keyboard *input) {
    // Handle movement
    if (input->isKeyDown(OIS::KC_W)) {
        mMainNode->translate(mMainNode->getOrientation() * Vector3(0, 0, 100 * elapsedTime));
    }
    if (input->isKeyDown(OIS::KC_S)) {
        mMainNode->translate(mMainNode->getOrientation() * Vector3(0, 0, -50 * elapsedTime));
    }
    if (input->isKeyDown(OIS::KC_A)) {
        mMainNode->yaw(Radian(2 * elapsedTime));
    }
    if (input->isKeyDown(OIS::KC_D)) {
        mMainNode->yaw(Radian(-2 * elapsedTime));
    }
}

// Change visibility - Useful for 1st person view ;)

void Player::setVisible(bool visible) {
    mMainNode->setVisible(visible);
}
