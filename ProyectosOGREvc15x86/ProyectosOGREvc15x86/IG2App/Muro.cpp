#include "Muro.h"

Muro::Muro()
{

}

Muro::Muro(Vector3 initPos, SceneNode* node, SceneManager* sceneMng)
	: Bloque(initPos, node, sceneMng)
{
	Ogre::Entity* cubo = mSM->createEntity("cube.mesh");
	node->attachObject(cubo);
	
}

Muro::~Muro()
{

}

//void Muro::init()
//{
//
//}
