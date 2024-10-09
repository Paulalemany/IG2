#include "Muro.h"

Muro::Muro()
{

}

Muro::Muro(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, bool pasable)
	: Bloque(initPos, node, sceneMng, pasable)
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
