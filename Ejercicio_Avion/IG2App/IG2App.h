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
#include <OgreBillboardSet.h>
#include <OgreParticleSystem.h>
#include <sstream>
#include <iostream>
#include <string>
//#include "DataSizes.h"


#include "Avion.h"

class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener{

public:
    explicit IG2App() : IG2ApplicationContext("IG2App") { };
    virtual ~IG2App() { };
 
protected:
    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
    virtual void shutdown();
    virtual void setup();
    virtual void setupScene();
    virtual void frameRendered(const Ogre::FrameEvent& evt);
    
private:
    
    //static const Vector3 CAMERA_INIT_POSITION;
        
    // Scene manager and tray system
    Ogre::SceneManager* mSM = nullptr;
    OgreBites::TrayManager* mTrayMgr = nullptr;
   
    // Camera
    Ogre::SceneNode* mCamNode = nullptr;
    OgreBites::CameraMan* mCamMgr = nullptr; 

    Avion* avion = nullptr;
    
};

#endif
