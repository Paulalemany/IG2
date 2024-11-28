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

    danceTime = durStep[0] * 1000;
    movingTime = durStep[7] * 1000;

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
    Vector3 keyframePos(0, 0, 0);
    Quaternion keyframeRot(0, 0, 0, 0);

    durStep[0] = 3;    // duracion kf 0
    durStep[1] = 1 + durStep[0];      // kf1 + acumulado
    durStep[2] = 3 + durStep[1];      // kf2 + acumulado
    durStep[3] = 1 + durStep[2];      // kf3 + acumulado
    durStep[4] = 3 + durStep[3];      // kf4 + acumulado
    durStep[5] = 3 + durStep[4];      // kf5 + acumulado
    durStep[6] = 1 + durStep[5];      // kf6 + acumulado
    durStep[7] = 3 + durStep[6];      // kf7 + acumulado
    durStep[8] = 3 + durStep[7];    // kf8 + acumulado -> suma 21 que seria la duracion total

    animation = sm->createAnimation("sinbadMoving", durStep[8]); // importante la duracion total!!
    animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
    NodeAnimationTrack* track = animation->createNodeTrack(0);
    track->setAssociatedNode(sinbadNode);

    // Keyframes
    TransformKeyFrame* kf;

    // Keyframe 0 (Init state)
    kf = track->createNodeKeyFrame(0);
    keyframeRot = Quaternion(Degree(0), Vector3(0, 1, 0));

    kf->setRotation(keyframeRot);
    kf->setTranslate(keyframePos);

    // Keyframe 1 Quieto
    kf = track->createNodeKeyFrame(durStep[0]);
    keyframeRot = Quaternion(Degree(0), Vector3(0, 1, 0));

    kf->setRotation(keyframeRot);
    kf->setTranslate(keyframePos);

    // Keyframe 2: Giro a la derecha
    kf = track->createNodeKeyFrame(durStep[1]);
    keyframeRot = Quaternion(Degree(90), Vector3(0, 1, 0));

    kf->setRotation(keyframeRot);
    kf->setTranslate(keyframePos);

    // Keyframe 3 Movimiento a la derecha
    kf = track->createNodeKeyFrame(durStep[2]);
    keyframePos += Ogre::Vector3::UNIT_X * movementLength;
    keyframeRot = Quaternion(Degree(90), Vector3(0, 1, 0));

    kf->setRotation(keyframeRot);
    kf->setTranslate(keyframePos);

    //  Keyframe 4 Giro a la izquierda
    kf = track->createNodeKeyFrame(durStep[3]);
    keyframeRot = Quaternion(Degree(-90), Vector3(0, 1, 0));

    kf->setRotation(keyframeRot);
    kf->setTranslate(keyframePos);

    // Keyframe 5: Movimiento a la izquierda
    kf = track->createNodeKeyFrame(durStep[4]);
    keyframePos += Ogre::Vector3::NEGATIVE_UNIT_X * movementLength;

    kf->setRotation(keyframeRot);
    kf->setTranslate(keyframePos);

    // Keyframe 6: + Movimiento a la izquierda
    kf = track->createNodeKeyFrame(durStep[5]);
    keyframePos += Ogre::Vector3::NEGATIVE_UNIT_X * movementLength;

    kf->setRotation(keyframeRot);
    kf->setTranslate(keyframePos);

    //  Keyframe 7 Giro a la derecha
    kf = track->createNodeKeyFrame(durStep[6]);
    keyframeRot = Quaternion(Degree(90), Vector3(0, 1, 0));

    kf->setRotation(keyframeRot);
    kf->setTranslate(keyframePos);

    // Keyframe 8: Movimiento a la derecha
    kf = track->createNodeKeyFrame(durStep[7]);
    keyframePos += Ogre::Vector3::UNIT_X * movementLength;

    kf->setRotation(keyframeRot);
    kf->setTranslate(keyframePos);

    //  Keyframe 9 Giro al frente para repetir animacion
    kf = track->createNodeKeyFrame(durStep[8]);
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
    isRunning = false;

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

        timer->reset();
    }

    if (timer->getMilliseconds() >= movingTime
        && animationStateRunBase->getEnabled()
        && animationStateRunTop->getEnabled())
    {
        animationStateRunTop->setEnabled(false);
        animationStateRunBase->setEnabled(false);

        animationStateDance->setEnabled(true); // vuelve a bailar

        timer->reset();
    }

    animationState->addTime(evt.timeSinceLastFrame);
    animationStateRunBase->addTime(evt.timeSinceLastFrame);
    animationStateRunTop->addTime(evt.timeSinceLastFrame);
    animationStateDance->addTime(evt.timeSinceLastFrame);

}