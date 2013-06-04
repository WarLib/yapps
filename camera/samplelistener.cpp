#include "samplelistener.hpp"

SampleListener::SampleListener(RenderWindow* win, Camera* cam)
	: ExampleFrameListener(win, cam) {
		mChar = 0;
		mExCamera = 0;
		mMode = 1;
}

void SampleListener::setCharacter(Char *character) {
	mChar = character;
}

void SampleListener::setExtendedCamera(ExtendedCamera *cam) {
	mExCamera = cam;
}

bool SampleListener::frameStarted(const FrameEvent& evt) {
	mKeyboard->capture();

	if (mChar) {
		mChar->update(evt.timeSinceLastFrame, mKeyboard);

		if (mExCamera) {
			switch (mMode) {
			case 1: // 3rd person fixed
				mExCamera->update(evt.timeSinceLastFrame,
					Vector3(0, 40, 0),mChar->getSightNode()->_getDerivedPosition());
				break;
			case 2: // 1st person
				mExCamera->update(evt.timeSinceLastFrame,
					mChar->getWorldPosition(),mChar->getSightNode()->_getDerivedPosition());
				break;
			}
		}
	}

	// 3rd Person - Fixed Camera
	if (mKeyboard->isKeyDown(OIS::KC_F2)) {
		mMode = 1;
		if (mChar)
			static_cast<Player *> (mChar)->setVisible(true);
		if (mExCamera) {
			if (mChar)
				mExCamera->instantUpdate(Vector3(0, 40, 0), mChar->getSightNode()->_getDerivedPosition());
			mExCamera->setTightness(0.01f);
		}
	}
	// 1st Person
	if (mKeyboard->isKeyDown(OIS::KC_F3)) {
		mMode = 2;
		if (mChar)
			static_cast<Player *> (mChar)->setVisible(false);
		if (mExCamera) {
			if (mChar)
				mExCamera->instantUpdate(mChar->getCameraNode()->_getDerivedPosition(), mChar->getSightNode()->_getDerivedPosition());
			mExCamera->setTightness(1.0f);
		}
	}

	// Exit if we press Esc
	if (mKeyboard->isKeyDown(OIS::KC_ESCAPE))
		return false;

	return true;
}
