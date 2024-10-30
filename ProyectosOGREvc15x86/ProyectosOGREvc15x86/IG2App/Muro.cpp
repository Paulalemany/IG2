#include "Muro.h"

Muro::Muro()
{

}

Muro::Muro(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, string textura, bool pasable)
	: Bloque(initPos, node, sceneMng, pasable)
{
	Ogre::Entity* cubo = mSM->createEntity("cube.mesh");
	cubo->setMaterialName(textura);
	node->attachObject(cubo);
	
}

Muro::~Muro()
{

}


