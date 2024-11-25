#include "IntroScene.h"

IntroScene::IntroScene(Ogre::SceneManager* scene, OgreBites::TextBox* textB, Ogre::SceneNode* camNode)
{
	sm = scene;
	iTextBox = textB;
    camN = camNode;

    // Entidades
    sinbadEnt = sm->createEntity("Sinbad.mesh");
    sinbadNode = sm->getRootSceneNode()->createChildSceneNode();
    sinbadNode->attachObject(sinbadEnt);
    sinbadNode->scale(5, 5, 5);
    sinbadNode->setPosition(0, 25, 0); // On the floor!
    sinbadNode->setInitialState();

    // swords
    swordLeftEnt = sm->createEntity("Sword.mesh");
    swordRightEnt = sm->createEntity("Sword.mesh");

	addGround();

	configTextBox();

    configLight();

    configCamera();
    
    configAnims();

    // inicia el temporizador
    timer = new Ogre::Timer();


    ///-----------SISTEMA DE PARTICULAS--------------------
    fuego = sm->createParticleSystem("fueguito", "fireParticleSystem");
    SceneNode* fuegoNode = sm->getRootSceneNode()->createChildSceneNode();
    fuego->setEmitting(true);
    fuegoNode->attachObject(fuego);

    //fuegoNode->setPosition({ 100,0,0 });
}

void IntroScene::configTextBox()
{
	iTextBox->clearText();
	iTextBox->appendText("Pulsa S para iniciar el juego");

	iTextBox->refitContents();
}

void IntroScene::configLight()
{
    light = sm->createLight("DirectionalLight1");
    light->setType(Light::LT_DIRECTIONAL);
    light->setDiffuseColour(1.0f, 1.0f, 1.0f);

    // Node with the light attached
    Ogre::SceneNode* nodeDir = sm->getRootSceneNode()->createChildSceneNode();
    nodeDir->setDirection(Ogre::Vector3(0, -1, -1));
    nodeDir->attachObject(light);
}

void IntroScene::addGround()
{
    MeshManager::getSingleton().createPlane("floor", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        Plane(Vector3::UNIT_Y, 0),
        1500, 1500, 200, 200, true, 1, 5, 5,
        Vector3::UNIT_Z);

    // Creating the plane
    Entity* ent = sm->createEntity("exampleFloor", "floor");
    ent->setMaterialName("mat/MRAMOR");
    SceneNode* floor = sm->getRootSceneNode()->createChildSceneNode();
    floor->attachObject(ent);
}

void IntroScene::configCamera()
{
    camN->setPosition(0, 20, 130);
    camN->lookAt(Ogre::Vector3(0, 20, 0), Ogre::Node::TS_WORLD);

}

void IntroScene::configAnims()
{
    animationStateDance = sinbadEnt->getAnimationState("Dance");
    animationStateRunBase = sinbadEnt->getAnimationState("RunBase");
    animationStateRunTop = sinbadEnt->getAnimationState("RunTop");

    // Variables
    int movementLength = 50;
    Ogre::Real duration = 16.0;
    Vector3 keyframePos(0, 0, 0);
    Ogre::Real durStep = duration / 4.0;


    animation = sm->createAnimation("sinbadWalking", duration);
    animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
    NodeAnimationTrack* track = animation->createNodeTrack(0);
    track->setAssociatedNode(sinbadNode);

    // Keyframes
    TransformKeyFrame* kf;
    // Keyframe 0: Init state
    kf = track->createNodeKeyFrame(durStep * 0);
    kf->setTranslate(keyframePos);
    // Keyframe 1: Go to the right
    kf = track->createNodeKeyFrame(durStep * 1);
    keyframePos += Ogre::Vector3::UNIT_X * movementLength;
    kf->setTranslate(keyframePos);
    // Keyframe 2: Go to the initial position
    kf = track->createNodeKeyFrame(durStep * 2);
    keyframePos += Ogre::Vector3::NEGATIVE_UNIT_X * movementLength;
    kf->setTranslate(keyframePos);
    // Keyframe 3: Go to the left
    kf = track->createNodeKeyFrame(durStep * 3);
    keyframePos += Ogre::Vector3::NEGATIVE_UNIT_X * movementLength;
    kf->setTranslate(keyframePos);
    // Keyframe 4: Go to the right (initital position)
    kf = track->createNodeKeyFrame(durStep * 4);
    keyframePos += Ogre::Vector3::UNIT_X * movementLength;
    kf->setTranslate(keyframePos);

    // Our defined animation
    animationState = sm->createAnimationState("sinbadWalking");
    animationState->setLoop(true);
    animationState->setEnabled(true);

    isDancing = true;
    isMoving = false;
    isRunning = false;

    animationStateDance->setEnabled(true);

    //// pone a bailar y le quita las espadas
    //if (!isDancing) {
    //    isRunning = false;
    //    isDancing = true;
    //    animationStateDance->setEnabled(true);
    //    animationStateRunTop->setEnabled(false);
    //    animationStateRunBase->setEnabled(false);

    //    // le quita las espadas si las tiene
    //    if (attachedLeftSword) sinbadEnt->detachObjectFromBone(swordLeftEnt);
    //    if (attachedRightSword) sinbadEnt->detachObjectFromBone(swordRightEnt);
    //}

}

void IntroScene::frameRendered(const Ogre::FrameEvent& evt)
{
    // cuando lleguemos al danceTime pasamos a correr
    if (timer->getMilliseconds() >= danceTime && isDancing) {
        // pone a correr y le da las espadas
        if (!isRunning) {
            isDancing = false;
            isRunning = true;
            //isMoving = true;
            animationStateDance->setEnabled(false);
            animationStateRunTop->setEnabled(true);
            animationStateRunBase->setEnabled(true);

            //espadas (cuando llegue a la derecha)  // TO DO
            //sinbadEnt->attachObjectToBone("Hand.L", swordLeftEnt);
            //sinbadEnt->attachObjectToBone("Hand.R", swordRightEnt);
        }
        timer->reset();
    }
    else if (timer->getMilliseconds() >= movingTime && isRunning) {

    }

    // duda: como hacemos que se mueva hacia los lados y se reproduzca la animacion de correr a la vez?
    // tambien hay que girar a sinbad hacia la direccion a la que mire
    if (isMoving) {
        animationState->addTime(evt.timeSinceLastFrame); 
    }
    else if (isRunning) {
        animationStateRunBase->addTime(evt.timeSinceLastFrame);
        animationStateRunTop->addTime(evt.timeSinceLastFrame);
    }
    else if (isDancing) 
    {
        animationStateDance->addTime(evt.timeSinceLastFrame);
    }

}