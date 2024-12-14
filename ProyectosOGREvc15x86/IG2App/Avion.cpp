#include "Avion.h"

Avion::Avion(Vector3 initPos, Ogre::SceneNode* node, Ogre::SceneManager* sceneMng)
    :IG2Object(initPos, node, sceneMng)
{
    //Creamos el avion
    Entity* avion = mSM->createEntity("sphere.mesh");
    SceneNode* avionNode = node->createChildSceneNode();
    avionNode->attachObject(avion);
    avionNode->setScale(6, 1, 1);

    Entity* alas = mSM->createEntity("cube.mesh");
    SceneNode* alasNode = avionNode->createChildSceneNode();
    alasNode->attachObject(alas);
    alasNode->setScale(0.25, 0.1, 10);

    Entity* timon = mSM->createEntity("cube.mesh");
    SceneNode* timonNode = avionNode->createChildSceneNode();
    timonNode->attachObject(timon);
    timonNode->setScale(0.25, 1, 0.1);
    timonNode->setPosition(70, 90, 0);
    timonNode->roll(Degree(35));

    //Ponemos al piloto
    Entity* piloto = mSM->createEntity("ninja.mesh");
    SceneNode* pilotoNode = node->createChildSceneNode();
    pilotoNode->attachObject(piloto);
    pilotoNode->setPosition(-300, 0, 0);
    pilotoNode->yaw(Degree(90));

    h1Node = node->createChildSceneNode();
    Helice* h1 = new Helice(initPos, h1Node, mSM, 10, 10);
    h1->yaw(Degree(-90));
    h1->setScale({0.5, 0.5, 0.5});
    h1->setPosition({ -80, 0, -300 });

    h2Node = node->createChildSceneNode();
    Helice* h2 = new Helice(initPos, h2Node, mSM, 10, 10);
    h2->yaw(Degree(-90));
    h2->setScale({ 0.5, 0.5, 0.5 });
    h2->setPosition({ -80, 0, 300 });
}

void Avion::rotate()
{
    h1Node->roll(Degree(1));
    h2Node->roll(Degree(1));
}
