#include "IG2App.h"

using namespace Ogre;
using namespace std;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt){

    switch (evt.keysym.sym) {

        // ESC key finished the rendering...
    case SDLK_ESCAPE:
        getRoot()->queueEndRendering();
        break;

    case SDLK_k:
        cout << "Position of the camera: " << mCamNode->getPosition() << endl;
        break; 

    case SDLK_l:
        if (light->isVisible()) {
            light->setVisible(false);
            cout << "Luz apagada" << endl;
        }
        else {
            light->setVisible(true);
            cout << "Luz encendida en " 
                << mLightNode->getPosition().x << "," 
                << mLightNode->getPosition().y << ","
                << mLightNode->getPosition().z << endl;
        }

        break;

    case SDLK_UP:
        lab->getHero()->move(Vector3(0, 0, -1));
        break;

    case SDLK_DOWN:
        lab->getHero()->move(Vector3(0, 0, 1));
        break;

    case SDLK_RIGHT:
        lab->getHero()->move(Vector3(1, 0, 0));
        break;

    case SDLK_LEFT:

        lab->getHero()->move(Vector3(-1, 0, 0));

        //Puede que sea mejor hacer aqui el metodo, que tenemos referencia al laberinto y al heroe
       /* if (canMove(Vector3(-1, 0, 0))) {
            
        }*/
        
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

    /// Apartado 5 - Overlay System
    mLevelOverlayMgr = new OgreBites::TrayManager("LevelMngr", mWindow.render);
    mLabel = mLevelOverlayMgr->createLabel(OgreBites::TL_BOTTOMRIGHT, "stageLabel", "Stage", 200);
    mTextBox = mLevelOverlayMgr->createTextBox(OgreBites::TL_BOTTOMRIGHT, "gameTextBox", "Game Info", 200, 100);

    addInputListener(mLevelOverlayMgr);
    
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

    // POLI -> Modifico la camara para q el laberinto se vea desde arriba
    mCamNode->setPosition(0, 400, 2200);
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
    light = mSM->createLight("Luz");
    light->setDiffuseColour(0.75, 0.75, 0.75);

    mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
    mLightNode->attachObject(light);
    

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

    //------------------------------------------------------------------------
    //Creando un cubo 

    /*Ogre::Entity* cubo = mSM->createEntity("cube.mesh");
    
    mCubeNode->attachObject(cubo);
    
    Ogre::Entity* cubo2 = mSM->createEntity("cube.mesh");
    mCube2Node = mSM->getRootSceneNode()->createChildSceneNode("nCube2");
    mCube2Node->attachObject(cubo2);

    mCube2Node->setPosition(100, 0, 0);*/

    ///-------LABERINTO---------------------------------------------------------
    lab = new Laberinto(mSM, "stage1.txt", mTextBox);

    addInputListener(lab->getHero());

    ///-------SUELO-------------------------------------------------------------
    MeshManager::getSingleton().createPlane(
        "plane", 
        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        Plane(Vector3::UNIT_Y, 0),                              // orientacion del plano mediante la normal
        gridSize, gridSize,                                     // anchura
        gridSize/10, gridSize/10,                               // numero de segmentos 
        true, 1, 
        10, 10,                                                 // [!] veces que se repite la textura
        Vector3::UNIT_Z                                         // orientacion up 
    );

    Entity* planeEnt = mSM->createEntity("suelo", "plane");
    planeEnt->setMaterialName(lab->getTexture(2)); // CALIDAD FEAAAA
    SceneNode* planeNode = mSM->getRootSceneNode()->createChildSceneNode("planeNode");
    planeNode->attachObject(planeEnt);

    // para que cuadre con el laberinto:
    planeNode->setPosition(Vector3(-900, -50, -900));

    ///-----CONFIG DE LUCES----------------------------------------------------
    light->setType(lab->getTipoLuz());
    
    updateSpotlightPos(); // en el caso de que sea spotlight se actualizara
}

void IG2App::updateSpotlightPos()
{
    if (lab->getTipoLuz() == Ogre::Light::LT_SPOTLIGHT) {
        mLightNode->setDirection(Ogre::Vector3(0, -1, 0));

        int sX, sZ;
        sX = lab->getHero()->getPosition().x;
        sZ = lab->getHero()->getPosition().z;
        mLightNode->setPosition(Vector3(sX, 300, sZ));

    }
}

bool IG2App::canMove(Vector3 newDir)
{
    Bloque* block = lab->getBloque(lab->getHero()->getPosition() + (newDir * 100),
        0, lab->getLenght());
    return block->getTraspasable();
}




