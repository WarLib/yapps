#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include "char.hpp"

// Specialization of the Character class - Our dear Ogre :D

class Player : public Char {
    // Attributes ------------------------------------------------------------------------------
protected:
    String mName;
public:
    // Methods ---------------------------------------------------------------------------------
protected:
public:
    Player(String name, SceneManager *sceneMgr);
    ~Player();

    void update(Real elapsedTime, OIS::Keyboard *input);

    // Change visibility - Useful for 1st person view ;)
    void setVisible(bool visible);
};

#endif