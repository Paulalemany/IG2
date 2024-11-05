#include "Frankestein.h"

Frankestein::Frankestein()
{
}

Frankestein::Frankestein(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, int tipo)
    : Villano(initPos, node, sceneMng, tipo)
{

#pragma region Nodos
    ///NODOS
    //Nodo padre
    auto Ncuerpo = mNode->createChildSceneNode();

    //Nodos atachados al cuerpo
    Nnudo1 = Ncuerpo->createChildSceneNode();  //Vamos a rotar estos dos por lo que a lo mejor 
    Nnudo2 = Ncuerpo->createChildSceneNode();  //nos interesa guardarlo

    auto Npet = Ncuerpo->createChildSceneNode();    //Queremos que vaya junto a su dueno

    auto Narma1 = Ncuerpo->createChildSceneNode();

    auto Npat1_1 = Ncuerpo->createChildSceneNode();
    auto Npat1_2 = Ncuerpo->createChildSceneNode();

    //Nodos atachados al pet
    auto Narma2 = Npet->createChildSceneNode();

    auto Npat2_1 = Npet->createChildSceneNode();
    auto Npat2_2 = Npet->createChildSceneNode();

    //Ncuerpo->showBoundingBox(true);
    //Nnudo1->showBoundingBox(true);
    //Nnudo2->showBoundingBox(true);
    //Npet->showBoundingBox(true);
    //Narma1->showBoundingBox(true);
    //Npat1_1->showBoundingBox(true);
    //Npat1_2->showBoundingBox(true);
    //Npat1_2->showBoundingBox(true);
    //Narma2->showBoundingBox(true);
    //Npat2_1->showBoundingBox(true);
    //Npat2_2->showBoundingBox(true);
#pragma endregion

#pragma region Entidades
    //Cuerpo del enemigo ANTIGUO
    //Entity* Cuerpo = mSM->createEntity("jaiqua.mesh");
    //Ncuerpo->attachObject(Cuerpo);
    //Ncuerpo->setScale(6, 6, 6);
    //Ncuerpo->yaw(Ogre::Degree(180));
    //Ncuerpo->setPosition(0, 0, -350);

    // enemigo aplastado:
    Entity* Cuerpo = mSM->createEntity("jaiqua.mesh");
    Ncuerpo->attachObject(Cuerpo);
    Ncuerpo->setScale(3, 6, 0.7);
    Ncuerpo->setPosition(0, 0, -50);
    Ncuerpo->yaw(Ogre::Degree(180));


    AxisAlignedBox aab = Cuerpo->getBoundingBox();
    aab.scale(Vector3(0,0,0));


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

    Entity* Patines1_2 = mSM->createEntity("sphere.mesh");
    Npat1_2->attachObject(Patines1_2);
    Npat1_2->setScale(Vector3(0.5, 1, 2) * PatScale);
    Npat1_2->rotate(Quaternion(Radian(-0.25), Vector3(1, 1, 0)));
    Npat1_2->setPosition(Vector3(0, -1.5, -55));

    Entity* Patines2_1 = mSM->createEntity("sphere.mesh");
    Npat2_1->attachObject(Patines2_1);
    Npat2_1->setScale(Vector3(5, 10, 20) * PatScale);
    Npat2_1->rotate(Quaternion(Radian(-0.25), Vector3(0, 1, 0)));
    Npat2_1->setPosition(Vector3(-12, -28, 10));

    Entity* Patines2_2 = mSM->createEntity("sphere.mesh");
    Npat2_2->attachObject(Patines2_2);
    Npat2_2->setScale(Vector3(5, 10, 20) * PatScale);
    Npat2_2->rotate(Quaternion(Radian(-0.25), Vector3(0, -1, 0)));
    Npat2_2->setPosition(Vector3(12, -28, 10));
#pragma endregion

#pragma region AABB

    aab = Nudo->getBoundingBox();
    aab.scale(boxSize);

    aab = Nudo2->getBoundingBox();
    aab.scale(boxSize);

    aab = Pet->getBoundingBox();
    aab.scale(boxSize);

    aab = Arma->getBoundingBox();
    aab.scale(boxSize);

    aab = Arma2->getBoundingBox();
    aab.scale(boxSize);

    aab = Patines1_1->getBoundingBox();
    aab.scale(boxSize);

    aab = Patines1_2->getBoundingBox();
    aab.scale(boxSize);

    aab = Patines2_1->getBoundingBox();
    aab.scale(boxSize);

    aab = Patines2_2->getBoundingBox();
    aab.scale(boxSize);
#pragma endregion

}

void Frankestein::frameRendered(const Ogre::FrameEvent& evt)
{
    //Por ahora se que queremos que roten las cosas
    //El movimiento no se si debe ser el mismo que el de los enemigos normales
    Nnudo1->rotate(Quaternion(Radian(25), Vector3(0, 0, 1)));
    Nnudo2->rotate(Quaternion(Radian(-25), Vector3(0, 0, 1)));

    Villano::frameRendered(evt);
}
