#include "IG2App.h"

using namespace Ogre;
using namespace std;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt){
        
    // ESC key finished the rendering...
    if (evt.keysym.sym == SDLK_ESCAPE){
        getRoot()->queueEndRendering();
    }

    if (spotLight != nullptr) {
        switch (evt.keysym.sym)
        {
        case SDLK_a:
            nodeSpot->setPosition(nodeSpot->getPosition().x - 1, nodeSpot->getPosition().y, nodeSpot->getPosition().z);
            break;

        case SDLK_d:
            nodeSpot->setPosition(nodeSpot->getPosition().x + 1, nodeSpot->getPosition().y, nodeSpot->getPosition().z);
            break;

        default:
            break;
        }
    } 
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
    
    /*Ogre::Light* directionalLight = mSM->createLight("DirectionalLight");
    directionalLight->setType(Light::LT_DIRECTIONAL);
    directionalLight->setDiffuseColour(1.0f,1.0f,1.0f);*/

    //// Node with the light attached
    //Ogre::SceneNode* nodeDir = mSM->getRootSceneNode()->createChildSceneNode();
    //nodeDir->setDirection(Ogre::Vector3(0, -1, -1));
    //nodeDir->attachObject(directionalLight);

    /*spotLight = mSM->createLight();
    spotLight->setType(Light::LT_SPOTLIGHT);
    spotLight->setDiffuseColour(Ogre::ColourValue(0, 1, 1));

    nodeSpot = mSM->getRootSceneNode()->createChildSceneNode();
    nodeSpot->setDirection(Ogre::Vector3(-1, -0.5, -1));
    nodeSpot->attachObject(spotLight);
    nodeSpot->setPosition(200, 50, 150);*/

    Ogre::Light* pointLight = mSM->createLight();
    pointLight->setType(Light::LT_POINT);

    Ogre::SceneNode* Npoint = mSM->getRootSceneNode()->createChildSceneNode();
    Npoint->attachObject(pointLight);
    Npoint->setPosition(30, 50, 0);

    
    // Setting up the shadows
    mSM->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

    /*Ogre::SHADOWTYPE_STENCIL_MODULATIVE
    Ogre::SHADOWTYPE_STENCIL_ADDITIVE*/
    
    //------------------------------------------------------------------------
    //

     //Creamos un plano
    MeshManager::getSingleton().createPlane("suelo",
        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        Plane(Vector3::UNIT_Y, 0), 
        1080,   //Tamaño en x 
        800,     //tamaño en y 
        100, 80, true, 1.0, 
        5, 5.0, //veces que se repite la textura
        Vector3::UNIT_Z);

    Entity* suelo = mSM->createEntity("suelo");
    suelo->setMaterialName("piedras");
    //suelo->setMaterialName("cromado");
    //suelo->setMaterialName("aguita");
    SceneNode* Nsuelo = mSM->getRootSceneNode()->createChildSceneNode();
    Nsuelo->attachObject(suelo);

    //Ponemos ogrehead
    Entity* ogreHead = mSM->createEntity("ogrehead.mesh");
    SceneNode* Nogrehead = mSM->getRootSceneNode()->createChildSceneNode();
    Nogrehead->attachObject(ogreHead);
    Nogrehead->setPosition({ 0, 20, 0 });

    Entity* esfera = mSM->createEntity("uv_sphere.mesh");
    esfera->setMaterialName("colorRosa");
    SceneNode* Nesfera = mSM->getRootSceneNode()->createChildSceneNode();
    Nesfera->attachObject(esfera);
    Nesfera->setPosition({ 70, 20, 0 });
    Nesfera->setScale(0.25, 0.25, 0.25);

}

void IG2App::frameRendered(const Ogre::FrameEvent& evt){
}
