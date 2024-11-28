#include "IntroScene.h"

IntroScene::IntroScene(Ogre::SceneManager* scene, OgreBites::TextBox* textB, Ogre::SceneNode* camNode)
{
	sm = scene;
	iTextBox = textB;
    camN = camNode;

    /// Entidades

    // sinbad
    sinbadEnt = sm->createEntity("Sinbad.mesh");
    sinbadNode = sm->getRootSceneNode()->createChildSceneNode();
    sinbadNode->attachObject(sinbadEnt);
    sinbadNode->scale(5, 5, 5);
    sinbadNode->setPosition(0, 25, 0); // On the floor!
    sinbadNode->setInitialState();

    // ogrehead
    ogreheadEnt = sm->createEntity("ogrehead.mesh");
    ogreheadNode = sm->getRootSceneNode()->createChildSceneNode();
    ogreheadNode->attachObject(ogreheadEnt);

    ogreheadNode->setPosition(0, 25, 0); // On the floor!
    ogreheadNode->setInitialState();

    // swords
    swordLeftEnt = sm->createEntity("Sword.mesh");
    swordRightEnt = sm->createEntity("Sword.mesh");

	addGround();

	configTextBox();

    configLight();

    configCamera();
    
    configSinbadAnim();

    configOgreheadAnim();

    danceTime = sDurStep[0] * 1000;
    swordsTime = sDurStep[2] * 1000;
    movingTime = sDurStep[7] * 1000;

    // inicia el temporizador
    timer = new Ogre::Timer();


    ///-----------SISTEMA DE PARTICULAS--------------------
    
    //Fuegos de fondo
    for (int i = 0; i < 25; i++) {

        nodes.push_back(sm->getRootSceneNode()->createChildSceneNode());

        //Nombre para el sistema de particulas
        string name = "fuego" + to_string(i);
        fueguitos.push_back(
            sm->createParticleSystem(name, "fireParticleSystem"));
        fueguitos[i]->setEmitting(true);

        //Necesito que esten atachados a un nodo
        nodes[i]->attachObject(fueguitos[i]);
        nodes[i]->setPosition(pos);
        pos.x += 10;
    }

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

    //El suelo va a ser un espejo
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
    camN->setPosition(0, 25, 130);
    camN->lookAt(Ogre::Vector3(0, 20, 0), Ogre::Node::TS_WORLD);

}

void IntroScene::configSinbadAnim()
{
    animationStateDance = sinbadEnt->getAnimationState("Dance");
    animationStateRunBase = sinbadEnt->getAnimationState("RunBase");
    animationStateRunTop = sinbadEnt->getAnimationState("RunTop");

    // Variables
    int movementLength = 50;
    Vector3 keyframePos(0, 0, 0);
    Quaternion keyframeRot(0, 0, 0, 0);

    // duracion de los keyframes
    sDurStep[0] = 3;                   // kf 0
    sDurStep[1] = 1 + sDurStep[0];      // kf1 + acumulado
    sDurStep[2] = 3 + sDurStep[1];      // kf2 + acumulado
    sDurStep[3] = 1 + sDurStep[2];      // kf3 + acumulado
    sDurStep[4] = 3 + sDurStep[3];      // kf4 + acumulado
    sDurStep[5] = 3 + sDurStep[4];      // kf5 + acumulado
    sDurStep[6] = 1 + sDurStep[5];      // kf6 + acumulado
    sDurStep[7] = 3 + sDurStep[6];      // kf7 + acumulado
    sDurStep[8] = 3 + sDurStep[7];      // kf8 + acumulado -> suma 21 que seria la duracion total

    sinbadAnim = sm->createAnimation("sinbadMoving", sDurStep[8]); // importante la duracion total!!
    sinbadAnim->setInterpolationMode(Ogre::Animation::IM_SPLINE);
    NodeAnimationTrack* track = sinbadAnim->createNodeTrack(0);
    track->setAssociatedNode(sinbadNode);

    // Keyframes
    TransformKeyFrame* kf;

    // Keyframe 0 (Init state)
    kf = track->createNodeKeyFrame(0);
    keyframeRot = Quaternion(Degree(0), Vector3(0, 1, 0));

    kf->setRotation(keyframeRot);
    kf->setTranslate(keyframePos);

    // Keyframe 1 Quieto
    kf = track->createNodeKeyFrame(sDurStep[0]);
    keyframeRot = Quaternion(Degree(0), Vector3(0, 1, 0));

    kf->setRotation(keyframeRot);
    kf->setTranslate(keyframePos);

    // Keyframe 2: Giro a la derecha
    kf = track->createNodeKeyFrame(sDurStep[1]);
    keyframeRot = Quaternion(Degree(90), Vector3(0, 1, 0));

    kf->setRotation(keyframeRot);
    kf->setTranslate(keyframePos);

    // Keyframe 3 Movimiento a la derecha
    kf = track->createNodeKeyFrame(sDurStep[2]);
    keyframePos += Ogre::Vector3::UNIT_X * movementLength;
    keyframeRot = Quaternion(Degree(90), Vector3(0, 1, 0));

    kf->setRotation(keyframeRot);
    kf->setTranslate(keyframePos);

    //  Keyframe 4 Giro a la izquierda
    kf = track->createNodeKeyFrame(sDurStep[3]);
    keyframeRot = Quaternion(Degree(-90), Vector3(0, 1, 0));

    kf->setRotation(keyframeRot);
    kf->setTranslate(keyframePos);

    // Keyframe 5: Movimiento a la izquierda
    kf = track->createNodeKeyFrame(sDurStep[4]);
    keyframePos += Ogre::Vector3::NEGATIVE_UNIT_X * movementLength;

    kf->setRotation(keyframeRot);
    kf->setTranslate(keyframePos);

    // Keyframe 6: + Movimiento a la izquierda
    kf = track->createNodeKeyFrame(sDurStep[5]);
    keyframePos += Ogre::Vector3::NEGATIVE_UNIT_X * movementLength;

    kf->setRotation(keyframeRot);
    kf->setTranslate(keyframePos);

    //  Keyframe 7 Giro a la derecha
    kf = track->createNodeKeyFrame(sDurStep[6]);
    keyframeRot = Quaternion(Degree(90), Vector3(0, 1, 0));

    kf->setRotation(keyframeRot);
    kf->setTranslate(keyframePos);

    // Keyframe 8: Movimiento a la derecha
    kf = track->createNodeKeyFrame(sDurStep[7]);
    keyframePos += Ogre::Vector3::UNIT_X * movementLength;

    kf->setRotation(keyframeRot);
    kf->setTranslate(keyframePos);

    //  Keyframe 9 Giro al frente para repetir animacion
    kf = track->createNodeKeyFrame(sDurStep[8]);
    keyframeRot = Quaternion(Degree(0), Vector3(0, 1, 0));

    kf->setRotation(keyframeRot);
    kf->setTranslate(keyframePos);


    // Our defined animation
    animationState = sm->createAnimationState("sinbadMoving");
    animationState->setLoop(true);
    animationState->setEnabled(true);
    

    // aparte
    animationStateRunTop->setEnabled(false);
    animationStateRunBase->setEnabled(false);
    animationStateDance->setEnabled(true); // empieza bailando

    isDancing = false;
    isMoving = true; // movimiento
}

void IntroScene::configOgreheadAnim()
{
    // Variables
    int movementLength = 50;
    Vector3 keyframePos(0, 0, 0);
    Quaternion keyframeRot(0, 0, 0, 0);

    // duracion de los keyframes
    oDurStep[0] = 3;                   // kf 0
    oDurStep[1] = 3 + oDurStep[0];      // kf1 + acumulado
    oDurStep[2] = 3 + oDurStep[1];      // kf2 + acumulado
    oDurStep[3] = 1 + oDurStep[2];      // kf3 + acumulado
    oDurStep[4] = 3 + oDurStep[3];      // kf4 + acumulado
    oDurStep[5] = 3 + oDurStep[4];      // kf5 + acumulado

    ogreAnim = sm->createAnimation("ogreheadMoving", oDurStep[5]); // importante la duracion total!!
    ogreAnim->setInterpolationMode(Ogre::Animation::IM_SPLINE);
    NodeAnimationTrack* track = ogreAnim->createNodeTrack(0);
    track->setAssociatedNode(ogreheadNode);

    // Keyframes
    TransformKeyFrame* kf;

    // Keyframe 0 (Init state)
    kf = track->createNodeKeyFrame(0);
    keyframeRot = Quaternion(Degree(90), Vector3(0, 1, 0));
    keyframePos = Vector3(-100,0,0);

    kf->setRotation(keyframeRot);
    kf->setTranslate(keyframePos);

    // Keyframe 1 Movimiento a la derecha
    kf = track->createNodeKeyFrame(oDurStep[0]);
    keyframePos += Ogre::Vector3::UNIT_X * movementLength;

    kf->setRotation(keyframeRot);
    kf->setTranslate(keyframePos);

    // Keyframe 2: Movimiento a la derecha
    kf = track->createNodeKeyFrame(oDurStep[1]);

    keyframePos += Ogre::Vector3::UNIT_X * movementLength;

    kf->setRotation(keyframeRot);
    kf->setTranslate(keyframePos);

    // Keyframe 3 Giro a la izquierda
    kf = track->createNodeKeyFrame(oDurStep[2]);
    keyframeRot = Quaternion(Degree(-90), Vector3(0, 1, 0));

    kf->setRotation(keyframeRot);
    kf->setTranslate(keyframePos);

    //  Keyframe 4 Movimiento a la izquierda
    kf = track->createNodeKeyFrame(oDurStep[3]);
    keyframePos += Ogre::Vector3::NEGATIVE_UNIT_X * movementLength;

    kf->setRotation(keyframeRot);
    kf->setTranslate(keyframePos);

    // Keyframe 5: Giro a la derecha
    kf = track->createNodeKeyFrame(oDurStep[4]);
    keyframeRot = Quaternion(Degree(90), Vector3(0, 1, 0));

    kf->setRotation(keyframeRot);
    kf->setTranslate(keyframePos);

    // Keyframe 5: Movimiento a la izquierda y escala
    kf = track->createNodeKeyFrame(oDurStep[5]);
    keyframePos += Ogre::Vector3::UNIT_X * movementLength;
    
    kf->setScale(Vector3(0.1, 0.1, 0.1));
    kf->setRotation(keyframeRot);
    kf->setTranslate(keyframePos);



    // Our defined animation
    ogreheadAnimationState = sm->createAnimationState("ogreheadMoving");
    ogreheadAnimationState->setLoop(true);
    ogreheadAnimationState->setEnabled(true);

}

void IntroScene::stop()
{
    _stop = true;
}

void IntroScene::frameRendered(const Ogre::FrameEvent& evt)
{
    if (_stop) return;

    // cuando lleguemos al danceTime pasamos a correr
    if (timer->getMilliseconds() >= danceTime 
        && animationStateDance->getEnabled()) 
    {
        animationStateDance->setEnabled(false); // deja de bailar

        animationStateRunTop->setEnabled(true);
        animationStateRunBase->setEnabled(true);
    }

    if (timer->getMilliseconds() >= swordsTime
        && !swordsAttached)
    {
        sinbadEnt->attachObjectToBone("Hand.L", swordLeftEnt);
        sinbadEnt->attachObjectToBone("Hand.R", swordRightEnt);

        swordsAttached = true;
    }

    if (timer->getMilliseconds() >= movingTime
        && animationStateRunBase->getEnabled()
        && animationStateRunTop->getEnabled())
    {
        animationStateRunTop->setEnabled(false);
        animationStateRunBase->setEnabled(false);

        if (swordsAttached) {
            sinbadEnt->detachObjectFromBone(swordLeftEnt);
            sinbadEnt->detachObjectFromBone(swordRightEnt);

            swordsAttached = false;
        }

        animationStateDance->setEnabled(true); // vuelve a bailar
    }

    // cuando llega al final de la animacion reseteamos el timer
    if (timer->getMilliseconds() >= animationState->getLength() * 1000) 
    {
        timer->reset();
    }

    // para que se actualicen las animaciones
    animationState->addTime(evt.timeSinceLastFrame);
    ogreheadAnimationState->addTime(evt.timeSinceLastFrame);
    animationStateRunBase->addTime(evt.timeSinceLastFrame);
    animationStateRunTop->addTime(evt.timeSinceLastFrame);
    animationStateDance->addTime(evt.timeSinceLastFrame);

}