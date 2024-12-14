#include "IG2App.h"

using namespace Ogre;
using namespace std;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt){
        
    // ESC key finished the rendering...
    if (evt.keysym.sym == SDLK_ESCAPE){
        getRoot()->queueEndRendering();
    }

    switch (evt.keysym.sym)
    {
    case SDLK_a:
        //Giramos las esferas en el sentido positivo
        hoursNode->roll(Degree(1));
        break;
    case SDLK_s:
        //Giramos las esferas en el sentido negativo
        hoursNode->roll(Degree(-1));
        break;
    case SDLK_d:
        hourNode->roll(Degree(1));
        break;
    case SDLK_f:
        hourNode->roll(Degree(-1));
        break;
    default:
        break;
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
    //cam->setPolygonMode(Ogre::PM_WIREFRAME);
            
    mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
    mCamNode->attachObject(cam);

    mCamNode->setPosition(0, 0, 2500);
    mCamNode->lookAt(Ogre::Vector3(0, 200, 0), Ogre::Node::TS_WORLD);
    
    // and tell it to render into the main window
    Viewport* vp = getRenderWindow()->addViewport(cam);
    vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));
    
    mCamMgr = new OgreBites::CameraMan(mCamNode);
    addInputListener(mCamMgr);
    mCamMgr->setStyle(OgreBites::CS_ORBIT);
    
    
    //------------------------------------------------------------------------
    // Creating the light
    
    //mSM->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
    Ogre::Light* directionalLight = mSM->createLight("DirectionalLight");
    directionalLight->setType(Light::LT_DIRECTIONAL);
    directionalLight->setDiffuseColour(1.0f, 1.0f, 1.0f);

    // Node with the light attached
    Ogre::SceneNode* nodeDir = mSM->getRootSceneNode()->createChildSceneNode();
    nodeDir->setDirection(Ogre::Vector3(0, -1, -1));
    nodeDir->attachObject(directionalLight);
    

    //------------------------------------------------------------------------
    // Creating the clock

    ///Creamos las 12 esferas del reloj
    std::vector<Entity*> reloj;
    std::vector<SceneNode*> nodos;

    clockNode = mSM->getRootSceneNode()->createChildSceneNode(); //Se presupone que se pone en el 0,0 no?
    hoursNode = clockNode->createChildSceneNode();

    float x, y, z = 0;
    float r = 700;

    for (int i = 0; i < 12; i++) {

        float angle = Math::TWO_PI * i / 12;

        x = r * Math::Cos(angle);  //360grados / 12 esferas
        y = r * Math::Sin(angle);
        
        reloj.push_back(mSM->createEntity("sphere.mesh"));
        nodos.push_back(hoursNode->createChildSceneNode());

        nodos[i]->attachObject(reloj[i]);

        nodos[i]->setPosition(x, y, z);

        //hacemos más pequeñas las horas impares
        if (i % 2 != 0) nodos[i]->setScale(nodos[i]->getScale() / 2);

    }

    //Manecillas del reloj
    handNode = clockNode->createChildSceneNode();

    Entity* hourHand = mSM->createEntity("cube.mesh");
    hourNode = handNode->createChildSceneNode();
    SceneNode* hourHandNode = hourNode->createChildSceneNode();
    hourHandNode->attachObject(hourHand);
    hourHandNode->setPosition(200, 0, 0);
    hourHandNode->setScale(5, 0.5, 0.5);

    Entity* minuteHand = mSM->createEntity("cube.mesh");
    minNode = handNode->createChildSceneNode();
    SceneNode* minuteHandNode = minNode->createChildSceneNode();
    minuteHandNode->attachObject(minuteHand);
    minuteHandNode->setScale(5, 0.25, 0.25);
    minuteHandNode->setPosition(0,200, 0);
    minuteHandNode->roll(Degree(-90));
    
    Entity* secondHand = mSM->createEntity("cube.mesh");
    SceneNode* secondHandNode = minuteHandNode->createChildSceneNode();
    secondHandNode->attachObject(secondHand);
    secondHandNode->setPosition(70, 0, 0);
    secondHandNode->setScale(1, 0.5, 0.5);

}


