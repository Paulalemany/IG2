#include "IG2App.h"

using namespace Ogre;
using namespace std;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt){
        
    // ESC key finished the rendering...
    if (evt.keysym.sym == SDLK_ESCAPE){
        getRoot()->queueEndRendering();
    }
    else if (evt.keysym.sym == SDLK_k) {
        cout << "Position of Sinbad: " << mSinbadNode->getPosition() << endl;
        cout << "Position of Dragon: " << mDragonNode->getPosition() << endl;
        cout << "Position of the camera: " << mCamNode->getPosition() << endl;
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
    // (llama al setup del padre)
    IG2ApplicationContext::setup();

    // Create the scene manager
    mSM = mRoot->createSceneManager();

    // Registra el scene manager en el RTSS
    mShaderGenerator->addSceneManager(mSM);

    // Configuracion del overlay system
    mSM->addRenderQueueListener(mOverlaySystem);
    mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);
    mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT); // el cuadro de fps, etc
    addInputListener(mTrayMgr);
    
    // Anyade el objeto en el Listener
    addInputListener(this);

    // Invoca setupScene()
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

    mCamNode->setPosition(0, 0, 1000);
    mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
    
    // and tell it to render into the main window
    Viewport* vp = getRenderWindow()->addViewport(cam);
    vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));
    
    mCamMgr = new OgreBites::CameraMan(mCamNode);
    addInputListener(mCamMgr);
    mCamMgr->setStyle(OgreBites::CS_ORBIT);
    
    
    //------------------------------------------------------------------------
    // Creating the light
    
    mSM->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
    Light* luz = mSM->createLight("Luz");
    luz->setType(Ogre::Light::LT_DIRECTIONAL);
    luz->setDiffuseColour(0.75, 0.75, 0.75);

    mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
    //mLightNode = mCamNode->createChildSceneNode("nLuz");
    mLightNode->attachObject(luz);
    mLightNode->setDirection(Ogre::Vector3(0, 0, -1));
    

#pragma region Practica_0
#pragma region Bano Romano
    //
    //#pragma region Pj
    //    //------------------------------------------------------------------------
    //    // Creating Sinbad
    //
    //    Ogre::Entity* ent4 = mSM->createEntity("Sinbad.mesh");
    //    mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
    //    mSinbadNode->attachObject(ent4);
    //
    //    // Show bounding box
    //    mSinbadNode->showBoundingBox(true);
    //
    //    // Set position of Sinbad
    //    mSinbadNode->setPosition(0, 30, 0);
    //
    //    // Set scale of Sinbad
    //    mSinbadNode->setScale(20, 20, 20);
    //
    //    //mSinbadNode->setVisible(false);  
    //
    //
    //    //------------------------------------------------------------------------
    //    // Creating Dragon
    //
    //    //Ogre::Entity* ent2 = mSM->createEntity("ogrehead.mesh");
    //    //mDragonNode = mSM->getRootSceneNode()->createChildSceneNode("nDragon");
    //    //mDragonNode->attachObject(ent2);
    //
    //    //// Show bounding box
    //    //mDragonNode->showBoundingBox(false);
    //
    //    //mDragonNode->lookAt(Ogre::Vector3(0, 0, 1), Ogre::Node::TS_WORLD);
    //
    //    // Set position of Dragon
    //    //mDragonNode->setPosition(200, 200, 0);
    //#pragma endregion
    //
    //#pragma region Escenario
    //
    ////Columnas
    //    Ogre::Entity* ent = mSM->createEntity("Columns.mesh");
    //    mColumnsNode = mSM->getRootSceneNode()->createChildSceneNode("nColumns");
    //    mColumnsNode->attachObject(ent);
    //
    //    // Show bounding box
    //    //mColumnsNode->showBoundingBox(true);
    //
    //    // Set position of Sinbad
    //    mColumnsNode->setPosition(0, 0, 0);
    //
    //
    //    //mColumnsNode->yaw(Ogre::Degree(-45));
    //   //mColumnsNode->setVisible(false);
    //
    ////BathLower
    //    Ogre::Entity* ent2 = mSM->createEntity("RomanBathLower.mesh");
    //    //mColumnsNode = mSM->getRootSceneNode()->createChildSceneNode("nColumns");
    //    mColumnsNode->attachObject(ent2);
    //
    //    // Show bounding box
    //    //mColumnsNode->showBoundingBox(true);
    //
    //    // Set position of Sinbad
    //    mColumnsNode->setPosition(0, 0, 0);
    //
    //    //BathUpper
    //    Ogre::Entity* ent3 = mSM->createEntity("RomanBathUpper.mesh");
    //    //mColumnsNode = mSM->getRootSceneNode()->createChildSceneNode("nColumns");
    //    mColumnsNode->attachObject(ent3);
    //
    //    // Show bounding box
    //    //mColumnsNode->showBoundingBox(true);
    //
    //    // Set position of Sinbad
    //    mColumnsNode->setPosition(0, 0, 0);
    //#pragma endregion
#pragma endregion

#pragma region muneco nieve

    ////Nodo padre
    //mPadreNode = mSM->getRootSceneNode()->createChildSceneNode("nPadre");

    ////Nodo cuello
    //mCuelloNode = mPadreNode->createChildSceneNode("nCuello");

    ////Cabeza
    //Ogre::Entity* cabeza = mSM->createEntity("sphere.mesh");
    //mCabezaNode = mCuelloNode->createChildSceneNode("nCabeza");
    //mCabezaNode->attachObject(cabeza);
    //mCabezaNode->setPosition(0, 180, 0);

    ////OjoIzq
    //Ogre::Entity* ojoIzq = mSM->createEntity("sphere.mesh");
    //mOjoIzqNode = mCabezaNode->createChildSceneNode("nOjoIzq");
    //mOjoIzqNode->attachObject(ojoIzq);
    //mOjoIzqNode->setScale(0.1, 0.1, 0.1);
    //mOjoIzqNode->setPosition(-50, 0, 90);

    ////OjoDer
    //Ogre::Entity* ojoDer = mSM->createEntity("sphere.mesh");
    //mOjoDerNode = mCabezaNode->createChildSceneNode("nOjoDer");
    //mOjoDerNode->attachObject(ojoDer);
    //mOjoDerNode->setScale(0.1, 0.1, 0.1);
    //mOjoDerNode->setPosition(50, 0, 90);

    ////Cuerpo
    //Ogre::Entity* cuerpo = mSM->createEntity("sphere.mesh");
    //mCuerpoNode = mCuelloNode->createChildSceneNode("nCuerpo");
    //mCuerpoNode->attachObject(cuerpo);
    //mCuerpoNode->setScale(1.5, 1.5, 1.5);
    //mCuerpoNode->setPosition(0, -60, 0);

    ////Ombligo
    //Ogre::Entity* ombligo = mSM->createEntity("sphere.mesh");
    //mOmbligoNode = mCuerpoNode->createChildSceneNode("nOmbligo");
    //mOmbligoNode->attachObject(ombligo);
    //mOmbligoNode->setScale(0.1, 0.1, 0.1);
    //mOmbligoNode->setPosition(0, -40, 100);


#pragma endregion
#pragma endregion





}


