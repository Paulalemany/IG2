#include "Frankestein.h"

Frankestein::Frankestein()
{
}

Frankestein::Frankestein(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, int tipo)
    : Villano(initPos, node, sceneMng, tipo)
{
    timer = new Timer();

#pragma region Nodos

    //Nodo padre
    auto Ncuerpo = mNode->createChildSceneNode();

    //Nodos atachados al cuerpo
    Nnudo1 = Ncuerpo->createChildSceneNode();  //Vamos a rotar estos dos por lo que a lo mejor 
    Nnudo2 = Ncuerpo->createChildSceneNode();  //nos interesa guardarlo

    auto Npet = Ncuerpo->createChildSceneNode();    //Queremos que vaya junto a su dueno

    auto Narma1 = Ncuerpo->createChildSceneNode();

    Nbola1_1 = Ncuerpo->createChildSceneNode();
    Nbola1_2 = Nbola1_1->createChildSceneNode();
    Nbola1_3 = Nbola1_2->createChildSceneNode();

    //Nodos atachados al pet
    auto Narma2 = Npet->createChildSceneNode();

    Nbola2_1 = Npet->createChildSceneNode();
    Nbola2_2 = Nbola2_1->createChildSceneNode();
    Nbola2_3 = Nbola2_2->createChildSceneNode();
#pragma endregion

#pragma region Entidades

    // enemigo aplastado:
    Entity* Cuerpo = mSM->createEntity("jaiqua.mesh");
    Ncuerpo->attachObject(Cuerpo);
    Ncuerpo->setScale(3, 6, 0.7);
    Ncuerpo->setPosition(0, 0, -50);
    Ncuerpo->yaw(Ogre::Degree(180));

    Ncuerpo->showBoundingBox(true);


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


    //Esto van a dejar de ser patines ahora son bolas que estan en el arma y se mueven (me faltan 2)
    Entity* bola1_1 = mSM->createEntity("sphere.mesh");
    Nbola1_1->attachObject(bola1_1);
    Nbola1_1->setScale(Vector3(2, 1, 2) * PatScale);
    Nbola1_1->rotate(Quaternion(Radian(-0.25), Vector3(5, -1, 0)));
    Nbola1_1->setPosition(Vector3(7, 15, -57));

    Entity* bola1_2 = mSM->createEntity("sphere.mesh");
    Nbola1_2->attachObject(bola1_2);
    Nbola1_2->setScale(Vector3(0.25, 1, 0.25));
    Nbola1_2->setPosition(Vector3(0, -230, 0));

    Entity* bola1_3 = mSM->createEntity("sphere.mesh");
    Nbola1_3->attachObject(bola1_3);
    Nbola1_3->setScale(Vector3(1.5, 0.5, 1.5));
    Nbola1_3->setPosition(Vector3(0, -220, 0));



    Entity* bola2_1 = mSM->createEntity("sphere.mesh");
    Nbola2_1->attachObject(bola2_1);
    Nbola2_1->setScale(Vector3(16, 8, 16) * PatScale);
    Nbola2_1->rotate(Quaternion(Radian(0.25), Vector3(-5, 1, 0)));
    Nbola2_1->setPosition(Vector3(45, 40, 5));
    
    Entity* bola2_2 = mSM->createEntity("sphere.mesh");
    Nbola2_2->attachObject(bola2_2);
    Nbola2_2->setScale(Vector3(0.25, 1, 0.25));
    Nbola2_2->setPosition(Vector3(0, -230, 0));
    
    Entity* bola2_3 = mSM->createEntity("sphere.mesh");
    Nbola2_3->attachObject(bola2_3);
    Nbola2_3->setScale(Vector3(1.5, 0.5, 1.5));
    Nbola2_3->setPosition(Vector3(0, -220, 0));

    //mNode->setScale(100, 100, 100);

#pragma endregion

}

void Frankestein::frameRendered(const Ogre::FrameEvent& evt)
{
    //Por ahora se que queremos que roten las cosas
    //El movimiento no se si debe ser el mismo que el de los enemigos normales
    Nnudo1->rotate(Quaternion(Radian(25), Vector3(0, 0, 1)));
    Nnudo2->rotate(Quaternion(Radian(-25), Vector3(0, 0, 1)));

    //Cuando pase el tiempo necesario
    if (timer->getMilliseconds() > time) {

        //Cambiamos el sentido de la animacion y reseteamos el contador
        timer->reset();
        dir *= -1;
    }

    Nbola1_1->rotate(Quaternion(Radian(-0.01 * dir), Vector3(1, 0, 0)));
    Nbola1_2->rotate(Quaternion(Radian(-0.025 * dir), Vector3(1, 0, 0)));
    Nbola1_3->rotate(Quaternion(Radian(-0.5 * dir), Vector3(1, 0, 0)));
    
    Nbola2_1->rotate(Quaternion(Radian(-0.01 * dir), Vector3(0, 1, 1)));
    Nbola2_2->rotate(Quaternion(Radian(-0.025 * dir), Vector3(0, 1, 1)));
    Nbola2_3->rotate(Quaternion(Radian(-0.5 * dir), Vector3(0, 1, 1)));


    Villano::frameRendered(evt);
}
