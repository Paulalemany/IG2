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
#include <sstream>
#include <iostream>
#include <string>

#include "Laberinto.h"
#include "IntroScene.h"
#include "Heroe.h"
#include "Frankestein.h"

class MovablePlane;

class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener{

public:
    explicit IG2App() : IG2ApplicationContext("IG2App") { };  // new -> setup()
    virtual ~IG2App() { };                                    // delete -> shutdown()
 
protected:
    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
    virtual void setup();
    virtual void shutdown();
    virtual void setupScene();

    virtual void setupGameScene();
    virtual void setupIntroScene();
    
    
#pragma region practica_0
    /*Ogre::SceneNode* mSinbadNode = nullptr;
    Ogre::SceneNode* mDragonNode = nullptr;
    Ogre::SceneNode* mColumnsNode = nullptr;


    Ogre::SceneNode* mPadreNode = nullptr;
    Ogre::SceneNode* mCuelloNode = nullptr;

    Ogre::SceneNode* mCabezaNode = nullptr;
    Ogre::SceneNode* mOjoIzqNode = nullptr;
    Ogre::SceneNode* mOjoDerNode = nullptr;
    Ogre::SceneNode* mNarizNode = nullptr;
    Ogre::SceneNode* mBocaNode = nullptr;

    Ogre::SceneNode* mCuerpoNode = nullptr;
    Ogre::SceneNode* mOmbligoNode = nullptr;*/
#pragma endregion
      
    Ogre::SceneManager* mSM = nullptr;
    Ogre::SceneManager* IS = nullptr;
    Ogre::SceneManager* GS = nullptr;


    OgreBites::TrayManager* mTrayMgr = nullptr;
    OgreBites::TrayManager* mLevelOverlayMgr = nullptr;
    OgreBites::Label* mLabel;
    OgreBites::TextBox* mTextBox;
    
    Ogre::Light* light = nullptr;
    Ogre::SceneNode* mLightParent = nullptr;
    Ogre::SceneNode* mLightNode = nullptr;
   

    /// Camaras por escenas
    Viewport* vp = nullptr;

    //Smn
    Ogre::SceneNode* mCamNode = nullptr;
    OgreBites::CameraMan* mCamMgr = nullptr;

    //Intro
    Ogre::SceneNode* mIntroCamNode = nullptr;
    OgreBites::CameraMan* mICamMgr = nullptr;

    Laberinto* lab = nullptr;

    int scene = 0;
    enum _scene {
        _Intro,
        _Game
    };
    
    IntroScene* intro = nullptr;
};

#endif
