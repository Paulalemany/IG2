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
#include "Heroe.h"

class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener{

public:
    explicit IG2App() : IG2ApplicationContext("IG2App") { };  // new -> setup()
    virtual ~IG2App() { };                                    // delete -> shutdown()
 
protected:
    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
    virtual void setup();
    virtual void shutdown();
    virtual void setupScene();
    
    
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

    //Ogre::SceneNode* mCubeNode = nullptr;
    //Ogre::SceneNode* mCube2Node = nullptr;
      
    Ogre::SceneManager* mSM = nullptr;
    OgreBites::TrayManager* mTrayMgr = nullptr;
    
    Ogre::Light* light = nullptr;
    Ogre::SceneNode* mLightParent = nullptr;
    Ogre::SceneNode* mLightNode = nullptr;
    
    Ogre::SceneNode* mCamNode = nullptr;
    OgreBites::CameraMan* mCamMgr = nullptr;

    Laberinto* lab = nullptr;
};

#endif
