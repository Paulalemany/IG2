#include "Perla.h"

Perla::Perla()
{

}

Perla::Perla(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, string textura, bool pasable, string psName)
	: Bloque(initPos, node, sceneMng, pasable)
{
	Ogre::Entity* esfera = mSM->createEntity("sphere.mesh");
	esfera->setMaterialName(textura);
	node->attachObject(esfera);
	node->setScale(0.1, 0.1, 0.1);

	this->setEntity(esfera);

	//------ SISTEMA DE PARTICULAS ----------------------------------------------------------
	cout << psName << endl;
	pSys = sceneMng->createParticleSystem(psName, "smokeParticleSystem");
	SceneNode* mPSNode = node->createChildSceneNode();
	pSys->setEmitting(true);
	mPSNode->attachObject(pSys);
}

Perla::~Perla()
{

}

