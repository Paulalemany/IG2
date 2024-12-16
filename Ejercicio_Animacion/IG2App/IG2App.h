#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <OgreEntity.h>
#include <OgreSkeletonInstance.h>
#include <OgreBone.h>
#include <OgreKeyFrame.h>
#include <sstream>
#include <iostream>
#include <string>

class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener{

public:
    explicit IG2App() : IG2ApplicationContext("IG2App") { };
    virtual ~IG2App() { };
 
protected:
    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
    virtual void setup();
    virtual void shutdown();
    virtual void setupScene();
    virtual void frameRendered(const Ogre::FrameEvent& evt);
    
private:
    
    // Sinbad and swords
    Ogre::SceneNode* sinbadNode = nullptr;
    Ogre::Entity * sinbadEnt;
    Ogre::Entity * swordLeftEnt;
    Ogre::Entity * swordRightEnt;
    
    // Flags to control the attached swords
    bool attachedLeftSword = false;
    bool attachedRightSword = false;
    
    // Lights
    Ogre::Light* spotLight1;
    Ogre::Light* spotLight2;
    Ogre::SceneNode* nodeSpot1 = nullptr;
    Ogre::SceneNode* nodeSpot2 = nullptr;
    int dynamicComponent = 0;
    
    // Animation state
    Ogre::AnimationState * animationState;
    
    // Animation states for Sinbad
    Ogre::AnimationState* animationStateDance;
    Ogre::AnimationState* animationStateRunBase;
    Ogre::AnimationState* animationStateRunTop;
    
    // Flags to control the animations
    bool isDancing = false;
    bool isRunning = false;
    
    // Scene manager and tray system
    Ogre::SceneManager* mSM = nullptr;
    OgreBites::TrayManager* mTrayMgr = nullptr;
   
    // Camera
    Ogre::SceneNode* mCamNode = nullptr;
    OgreBites::CameraMan* mCamMgr = nullptr;

    Ogre::Animation* animation;

    Ogre::Vector3 origen = { 0, 25, 0 };
    Ogre::Vector3 derecha = { 60, 0, 0 };
    Ogre::Vector3 izquierda = { -60, 0, 0 };

    int movementLenght = 60;
    Ogre::Real duration = 24.0;
    Ogre::Vector3 keyFramePos = { 0,0,0 };
    Ogre::Real durStep = duration / 4;
};

#endif
