#include "char.hpp"


SceneNode *Char::getSightNode() {
    return mSightNode;
}

SceneNode *Char::getCameraNode() {
    return mCameraNode;
}

Vector3 Char::getWorldPosition() {
    return mMainNode->_getDerivedPosition();
}