#include "IG2App.h"

using namespace Ogre;
using namespace std;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt){
        
    // ESC key finished the rendering...
    if (evt.keysym.sym == SDLK_ESCAPE){
        getRoot()->queueEndRendering();
    }
       
      
  return true;
}

void IG2App::shutdown(){
    
  mShaderGenerator->removeSceneManager(mSM);
  mSM->removeRenderQueueListener(mOverlaySystem);  
					
  mRoot->destroySceneManager(mSM);  

  delete mTrayMgr;  mTrayMgr = nullptr;
  delete mCamMgr; mCamMgr = nullptr;
  
  // do not forget to call the base 
  IG2ApplicationContext::shutdown(); 
}

void IG2App::setup(void){
    
    // do not forget to call the base first
    IG2ApplicationContext::setup();

    // Create the scene manager
    mSM = mRoot->createSceneManager();

    // Register our scene with the RTSS
    mShaderGenerator->addSceneManager(mSM);

    mSM->addRenderQueueListener(mOverlaySystem);
    mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);
    mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    addInputListener(mTrayMgr);
    
    // Adds the listener for this object
    addInputListener(this);
    setupScene();
}

void IG2App::setupScene(void){
    
    //------------------------------------------------------------------------
    // Creating the camera
    
    Camera* cam = mSM->createCamera("Cam");
    cam->setNearClipDistance(1);
    cam->setFarClipDistance(10000);
    cam->setAutoAspectRatio(true);
            
    mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
    mCamNode->attachObject(cam);
    mCamNode->setPosition(0, 0, 600);
    mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
    
    mCamMgr = new OgreBites::CameraMan(mCamNode);
    addInputListener(mCamMgr);
    mCamMgr->setStyle(OgreBites::CS_ORBIT);
    
    // and tell it to render into the main window
    Viewport* vp = getRenderWindow()->addViewport(cam);
    //vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));
        
    
    //------------------------------------------------------------------------
    // Creating the floor
    
    MeshManager::getSingleton().createPlane("floor", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                                            Plane(Vector3::UNIT_Y, 0),
                                            500, 500, 200, 200, true, 1, 1, 1,
                                            Vector3::UNIT_Z);
    
    // Creating the plane
    Entity* ent = mSM->createEntity ("exampleFloor", "floor");
    SceneNode* floor = mSM->getRootSceneNode()->createChildSceneNode();
    floor->attachObject(ent);
    
    //------------------------------------------------------------------------
    // Creating the light (Directional light)

    Ogre::Light* directionalLight1 = mSM->createLight("DirectionalLight");
    directionalLight1->setType(Light::LT_DIRECTIONAL);
    directionalLight1->setDiffuseColour(1.0f,1.0f,1.0f);

    // Node with the light attached
    Ogre::SceneNode* nodeDir = mSM->getRootSceneNode()->createChildSceneNode();
    nodeDir->setDirection(Ogre::Vector3(0, -1, -1));
    nodeDir->attachObject(directionalLight1);
    
    // Setting up the shadows
    //mSM->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

            
    //------------------------------------------------------------------------
    // Creating Sinbad
            
    sinbadEnt = mSM->createEntity("Sinbad.mesh");
    sinbadNode = mSM->getRootSceneNode()->createChildSceneNode();
    sinbadNode->attachObject(sinbadEnt);
    sinbadNode->scale(10, 10, 10);
    sinbadNode->setPosition(0, 50, 0); // On the floor!
    sinbadNode->setInitialState();
    
    
        
    //------------------------------------------------------------------------
    // Multitexturing...
    
    //ent->setMaterialName("agualuz");
    //ent->setMaterialName("aguadarks");
    ent->setMaterialName("aguasucia");
    
    
    
    //------------------------------------------------------------------------
    // Skyplane
    
    Ogre::Plane plane; plane.d = 1000; plane.normal = Ogre::Vector3::NEGATIVE_UNIT_Y; 
    mSM->setSkyPlane(true, plane, "cielo", 1500, 50, true, 1.5, 50, 50);
        
}

void IG2App::frameRendered(const Ogre::FrameEvent& evt){
}

