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
    case SDLK_a:    // Attach/Dettach left sword
        if (attachedLeftSword) {
            sinbadEnt->detachObjectFromBone(swordLeftEnt);
            attachedLeftSword = false;
        }
        else {  //No está atachada
            sinbadEnt->attachObjectToBone("Handle.L", swordLeftEnt);
            attachedLeftSword = true;
        }
        break;

    case SDLK_s:    // Attach/Dettach right sword
        if (attachedRightSword) {
            sinbadEnt->detachObjectFromBone(swordRightEnt);
            attachedRightSword = false;
        }
        else {  //No está atachada
            sinbadEnt->attachObjectToBone("Handle.R", swordRightEnt);
            attachedRightSword = true;
        }
        break;

    case SDLK_d:

        if (isDancing) { isDancing = false; }
        else {  //No esta bailando
            isDancing = true;
            isRunning = false;
        }

        animationStateDance->setEnabled(isDancing);
        animationStateDance->setLoop(isDancing);
        break;

    case SDLK_r:

        if (isRunning) { 
            isRunning = false; 
         
        }
        else {
            isRunning = true;
            isDancing = false;
        }
        animationStateRunTop->setEnabled(isRunning);
        animationStateRunTop->setLoop(isRunning);

        animationStateRunBase->setEnabled(isRunning);
        animationStateRunBase->setLoop(isRunning);

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
            
    mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
    mCamNode->attachObject(cam);
    mCamNode->setPosition(0, 0, 600);
    mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
    
    mCamMgr = new OgreBites::CameraMan(mCamNode);
    addInputListener(mCamMgr);
    mCamMgr->setStyle(OgreBites::CS_ORBIT);
    
    // and tell it to render into the main window
    Viewport* vp = getRenderWindow()->addViewport(cam);
    vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));
        
    
    //------------------------------------------------------------------------
    // Creating the floor
    
    MeshManager::getSingleton().createPlane("floor", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                                            Plane(Vector3::UNIT_Y, 0),
                                            1500, 1500, 200, 200, true, 1, 5, 5,
                                            Vector3::UNIT_Z);
    
    // Creating the plane
    Entity* ent = mSM->createEntity ("exampleFloor", "floor");
    ent->setMaterialName("example/stonesFloor");
    SceneNode* floor = mSM->getRootSceneNode()->createChildSceneNode();
    floor->attachObject(ent);
    
    
    //------------------------------------------------------------------------
    // Creating the light (Directional light)

    Ogre::Light* directionalLight1 = mSM->createLight("DirectionalLight1");
    directionalLight1->setType(Light::LT_DIRECTIONAL);
    directionalLight1->setDiffuseColour(1.0f,1.0f,1.0f);

    // Node with the light attached
    Ogre::SceneNode* nodeDir = mSM->getRootSceneNode()->createChildSceneNode();
    nodeDir->setDirection(Ogre::Vector3(0, -1, -1));
    nodeDir->attachObject(directionalLight1);
    
    // Setting up the shadows
    //mSM->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
    
    
    //------------------------------------------------------------------------
    // Creating the light (Spot light) -> Just for checking the numeric value animation
    
    // The light
//    spotLight1 = mSM->createLight("SpotLight1");
//    spotLight1->setType(Light::LT_SPOTLIGHT);
//    spotLight1->setDiffuseColour(1.0f, 0.0f, 0.0f);
//    
//    // Node with the light attached
//    nodeSpot1 = mSM->getRootSceneNode()->createChildSceneNode();
//    nodeSpot1->setPosition(100,200,0);
//    nodeSpot1->setDirection(Ogre::Vector3(0,-1,0));
//    nodeSpot1->attachObject(spotLight1);
//    
//    spotLight2 = mSM->createLight("SpotLight2");
//    spotLight2->setType(Light::LT_SPOTLIGHT);
//    spotLight2->setDiffuseColour(0.0f, 1.0f, 0.0f);
//
//    // Node with the light attached
//    nodeSpot2 = mSM->getRootSceneNode()->createChildSceneNode();
//    nodeSpot2->setPosition(0,200,0);
//    nodeSpot2->setDirection(Ogre::Vector3(0,-1,0));
//    nodeSpot2->attachObject(spotLight2);
    
        
    //------------------------------------------------------------------------
    // Creating Sinbad
    
    sinbadEnt = mSM->createEntity("Sinbad.mesh");
    sinbadNode =  mSM->getRootSceneNode()->createChildSceneNode();
    sinbadNode->attachObject(sinbadEnt);
    sinbadNode->scale(5, 5, 5);
    sinbadNode->setPosition(origen); // On the floor!
    //sinbadNode->rotate(Quaternion(Degree(90), { 0,1,0 }));
    sinbadNode->setInitialState();
    
    
    
    // Creating two swords
    swordLeftEnt = mSM->createEntity("Sword.mesh");
    swordRightEnt = mSM->createEntity("Sword.mesh");
     
    // Obtain the names of all the animations in Sinbad.mesh
    //AnimationStateSet * aux = sinbadEnt->getAllAnimationStates();
    //auto it = aux->getAnimationStateIterator().begin();
    //while (it != aux->getAnimationStateIterator().end()){
    //    auto s = it->first;
    //    ++it;
    //    cout << "Animation name (Sinbad.mesh): " << s << endl;
    //}
    
    // Obtain the names of all the bones in Sinbad.mesh
    /*SkeletonInstance * skeleton = sinbadEnt->getSkeleton();
    int numBones = skeleton->getNumBones();
    for (int i=0; i<numBones; i++){
        cout << "Bone name (Sinbad.mesh): " << skeleton->getBone(i)->getName() << endl;
    }*/

    
    //------------------------------------------------------------------------
    
    ///Desplazamiento lateral
    //7 KeyFrames -> origen, derecha, origen, izquierda, origen
    //Para que haga buen loop debe terminar en el mismo punto en el que empieza
    //Duracion total: 24
    //Duracion entre un KF y el siguiente: 4 (durStep = 4 = duracionTotal / 4)
    //Longitud del desplazamiento = 60

    // Animation of Sinbad
    animation = mSM->createAnimation("DesplazamientoAnim", duration);
    animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
    NodeAnimationTrack* track = animation->createNodeTrack(0);
    track->setAssociatedNode(sinbadNode);
    TransformKeyFrame* kf;

    Quaternion keyFrameRot(Degree(90), { 0,1,0 });
    
    /// Set keyframes here...
    //KeyFrame 0 (initState)
    kf = track->createNodeKeyFrame(durStep * 0);
    kf->setTranslate(keyFramePos);
    kf->setRotation(keyFrameRot);

    //KeyFrame 1 (Vamos para la derecha)
    kf = track->createNodeKeyFrame(durStep * 1);
    keyFramePos += derecha;
    kf->setTranslate(keyFramePos);
    kf->setRotation(keyFrameRot);

    //keyFrame 2 (Rotacion de 180)
    kf = track->createNodeKeyFrame(durStep * 2);
    keyFrameRot = Quaternion(Degree(-90), { 0,1,0 });
    kf->setTranslate(keyFramePos);
    kf->setRotation(keyFrameRot);

    //keyFrame 3 (volvemos al centro)
    kf = track->createNodeKeyFrame(durStep * 3);
    keyFramePos += izquierda;
    kf->setTranslate(keyFramePos);
    kf->setRotation(keyFrameRot);

    //keyFrame 4 (Vamos para la izquierda)
    kf = track->createNodeKeyFrame(durStep * 4);
    keyFramePos += izquierda;
    kf->setTranslate(keyFramePos);
    kf->setRotation(keyFrameRot);

    //keyFrame 5 (Rotacion de 180)
    kf = track->createNodeKeyFrame(durStep * 5);
    keyFrameRot = Quaternion(Degree(-90), { 0,1,0 });
    kf->setTranslate(keyFramePos);
    kf->setRotation(keyFrameRot);

    //keyFrame 6 (volvemos al centro)
    kf = track->createNodeKeyFrame(durStep * 6);
    keyFramePos += derecha;
    kf->setTranslate(keyFramePos);
    kf->setRotation(keyFrameRot);
    
    /// Our defined animation
    animationState = mSM->createAnimationState("DesplazamientoAnim");
    animationState->setEnabled(true);
    animationState->setLoop(true);

    animationStateDance = sinbadEnt->getAnimationState("Dance");
    animationStateRunTop = sinbadEnt->getAnimationState("RunTop");
    animationStateRunBase = sinbadEnt->getAnimationState("RunBase");
}

void IG2App::frameRendered(const Ogre::FrameEvent& evt){
        
    // Example of numeric value animation (lights)
    //------------------------------------------------------------------------
    
//    dynamicComponent = (dynamicComponent + ((int) (evt.timeSinceLastFrame * 1000))) % 3000;
//    spotLight1->setDiffuseColour(1.0f, dynamicComponent/3000.0, 0.0f);
//    spotLight2->setDiffuseColour(1.0f, 0.0f, dynamicComponent/3000.0);
        
    
    // Example of scene node animation (Sinbad)
    //------------------------------------------------------------------------
    //sinbadNode->yaw(Ogre::Degree(30 * evt.timeSinceLastFrame));
        
    
    // Example of NodeAnimationTrack
    //------------------------------------------------------------------------
    // TODO...
    
    
    // Example of Sinbad's animation (running and dancing)
    //------------------------------------------------------------------------
    
    if (isDancing) animationStateDance->addTime(evt.timeSinceLastFrame);
    else if (isRunning) {
        animationStateRunTop->addTime(evt.timeSinceLastFrame);
        animationStateRunBase->addTime(evt.timeSinceLastFrame);
    }
    
    animationState->addTime(evt.timeSinceLastFrame);
    
}

