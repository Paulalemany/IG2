#include "Frankestein.h"

Frankestein::Frankestein()
{
}

Frankestein::Frankestein(Vector3 initPos, SceneNode* node, SceneManager* sceneMng)
    : Villano(initPos, node, sceneMng)
{
    Ogre::Entity* Cuerpo = mSM->createEntity("jaiqua.mesh");

    Ogre::Entity* Nudo = mSM->createEntity("knot.mesh");
    Ogre::Entity* Nudo2 = mSM->createEntity("knot.mesh");

    Ogre::Entity* Pet = mSM->createEntity("penguin.mesh");

    Ogre::Entity* Arma = mSM->createEntity("spine.mesh");
    Ogre::Entity* Arma2 = mSM->createEntity("spine.mesh");

    Ogre::Entity* Patines1_1 = mSM->createEntity("spine.mesh");
    Ogre::Entity* Patines1_2 = mSM->createEntity("spine.mesh");
    Ogre::Entity* Patines2_1 = mSM->createEntity("spine.mesh");
    Ogre::Entity* Patines2_2 = mSM->createEntity("spine.mesh");

    node->attachObject(Cuerpo);
    node->attachObject(Nudo);
    node->setScale(10, 10, 10);

    //this->setEntity(Objeto);

    node->yaw(Ogre::Degree(180));
}
