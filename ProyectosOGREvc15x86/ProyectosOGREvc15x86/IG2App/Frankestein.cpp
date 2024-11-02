#include "Frankestein.h"

Frankestein::Frankestein()
{
}

Frankestein::Frankestein(Vector3 initPos, SceneNode* node, SceneManager* sceneMng)
    : Villano(initPos, node, sceneMng)
{
    ///NODOS
    //Nodo padre
    auto Ncuerpo = mNode->createChildSceneNode();

    //Nodos atachados al cuerpo
    auto Nnudo1 = Ncuerpo->createChildSceneNode();  //Vamos a rotar estos dos por lo que a lo mejor 
    auto Nnudo2 = Ncuerpo->createChildSceneNode();  //nos interesa guardarlo

    auto Npet = Ncuerpo->createChildSceneNode();    //Queremos que vaya junto a su dueno

    auto Narma1 = Ncuerpo->createChildSceneNode();

    auto Npat1_1 = Ncuerpo->createChildSceneNode();
    auto Npat1_2 = Ncuerpo->createChildSceneNode();

    //Nodos atachados al pet
    auto Narma2 = Npet->createChildSceneNode();
    
    auto Npat2_1 = Npet->createChildSceneNode();
    auto Npart2_2 = Npet->createChildSceneNode();


    //Cuerpo del enemigo
    Entity* Cuerpo = mSM->createEntity("jaiqua.mesh");
    Ncuerpo->attachObject(Cuerpo);


    Entity* Nudo = mSM->createEntity("knot.mesh");
    Nnudo1->attachObject(Nudo);
    Nnudo1->setScale(Vector3(1, 1, 1) * NodeScale);
    Nnudo1->setPosition(Vector3(1, 15, -55));

    Entity* Nudo2 = mSM->createEntity("knot.mesh");
    Nnudo2->attachObject(Nudo2);
    Nnudo2->setScale(Vector3(1, 1, 1) * NodeScale);
    Nnudo2->rotate(Quaternion(Radian(15), Vector3(1, 0, 1)));  //Lo giramos para que no esten exactamente iguales
    Nnudo2->setPosition(Vector3(1, 15, -55));


    Entity* Pet = mSM->createEntity("penguin.mesh");
    Npet->attachObject(Pet);
    Npet->yaw(Degree(180));
    Npet->setScale(Vector3(1, 1, 1) * PetScale);
    Npet->setPosition(Vector3(-2, 1, -55));


    Entity* Arma = mSM->createEntity("spine.mesh");
    Narma1->attachObject(Arma);
    Narma1->setScale(Vector3(1, 2, 1) * ArmaScale);
    Narma1->rotate(Quaternion(Radian(40), Vector3(0, 0, 1)));
    Narma1->setPosition(Vector3(6, 15, -57));

    Entity* Arma2 = mSM->createEntity("spine.mesh");
    Narma2->attachObject(Arma2);
    Narma2->setScale(Vector3(5, 10, 5) * ArmaScale);
    Narma2->rotate(Quaternion(Radian(-0.5), Vector3(0, 0, 1)));
    Narma2->setPosition(Vector3(20, -10, 0));

    Entity* Patines1_1 = mSM->createEntity("sphere.mesh");
    Npat1_1->attachObject(Patines1_1);
    Npat1_1->setScale(Vector3(0.5, 1, 2) * PatScale);
    Npat1_1->rotate(Quaternion(Radian(-0.25), Vector3(5, -1, 0)));
    Npat1_1->setPosition(Vector3(5, 0, -50));

    //Ogre::Entity* Patines1_2 = mSM->createEntity("sphere.mesh");
    //Ogre::Entity* Patines2_1 = mSM->createEntity("sphere.mesh");
    //Ogre::Entity* Patines2_2 = mSM->createEntity("sphere.mesh");

    /*node->attachObject(Cuerpo);
    node->attachObject(Nudo); */
    node->setScale(10, 10, 10);

    //this->setEntity(Objeto);

    node->yaw(Degree(180));
}
