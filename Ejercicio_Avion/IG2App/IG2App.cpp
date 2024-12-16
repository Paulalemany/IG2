#include "IG2App.h"

using namespace Ogre;
using namespace std;

// Initial position for the camera
//const Vector3 IG2App::CAMERA_INIT_POSITION = {0, 700, 1600};

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt){
        
    // ESC key finished the rendering...
    if (evt.keysym.sym == SDLK_ESCAPE){
        getRoot()->queueEndRendering();
    }

    if (evt.keysym.sym == SDLK_w) avion->rotate();
    
  return true;
}

void IG2App::shutdown(){
    
    mShaderGenerator->removeSceneManager(mSM);
    mSM->removeRenderQueueListener(mOverlaySystem);
            
    mRoot->destroySceneManager(mSM);

    delete mTrayMgr;
    mTrayMgr = nullptr;
    delete mCamMgr;
    mCamMgr = nullptr;

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
        
    mCamMgr = new OgreBites::CameraMan(mCamNode);
    addInputListener(mCamMgr);
    mCamMgr->setStyle(OgreBites::CS_ORBIT);
    mCamNode->setPosition({ 0, 700, 1600 });
    mCamNode->lookAt(Ogre::Vector3(0, 200, 0), Ogre::Node::TS_WORLD);
    
    // And tell it to render into the main window
    Viewport* vp = getRenderWindow()->addViewport(cam);
    vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));
    
    
    //------------------------------------------------------------------------
    // Creating the light (Directional light)

    //mSM->setAmbientLight(Ogre::ColourValue(0.3,0.3,0.3));
    
    Ogre::Light* directionalLight = mSM->createLight("DirectionalLight");
    directionalLight->setType(Light::LT_DIRECTIONAL);
    directionalLight->setDiffuseColour(1.0f,1.0f,1.0f);

    // Node with the light attached
    Ogre::SceneNode* nodeDir = mSM->getRootSceneNode()->createChildSceneNode();
    nodeDir->setDirection(Ogre::Vector3(0, -1, -1));
    nodeDir->attachObject(directionalLight);

    // Setting up the shadows
    //mSM->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
    
    
    
    
    
    //------------------------------------------------------------------------
    //

    /*SceneNode* aspaNode = mSM->getRootSceneNode()->createChildSceneNode();
    Helice* helice = new Helice({ 0,0,0 }, aspaNode, mSM, 10, 10);*/

    SceneNode* avionNode = mSM->getRootSceneNode()->createChildSceneNode();
    avion = new Avion({ 0,0,0 }, avionNode, mSM);   
}

void IG2App::frameRendered(const Ogre::FrameEvent& evt){
}
