#include "Helice.h"
#include <iostream>

Helice::Helice(Vector3 initPos, Ogre::SceneNode* node, Ogre::SceneManager* sceneMng, int n, int r)
	: IG2Object(initPos, node, sceneMng)
{
	//Colocamos las aspas formando un circulo
	float x, y, z = initPos.z;
	float angle;

	for (int i = 0; i < n; i++) {

		angle = (Math::TWO_PI * i) / n;	//Angulo donde colocar cada pala

		x = r * Math::Cos(angle);
		y = r * Math::Sin(angle);

		nodos.push_back(node->createChildSceneNode());
		palas.push_back(new Blade({ x, y, z }, nodos[i], sceneMng));

		palas[i]->roll(Degree((360 / n) * i));
	}

	//Colocamos el cilindro
	rotor = mSM->createEntity("Barrel.mesh");
	SceneNode* rotorNode = node->createChildSceneNode();
	rotorNode->attachObject(rotor);
	rotorNode->setScale(5, 5, 5);
	rotorNode->pitch(Degree(90));
}
