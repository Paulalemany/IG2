#include "Perla.h"

Perla::Perla()
{

}

Perla::Perla(Vector3 initPos, SceneNode* node, SceneManager* sceneMng)
	: IG2Object(initPos, node, sceneMng)
{
	Ogre::Entity* esfera = mSM->createEntity("sphere.mesh");
	node->attachObject(esfera);
	node->setScale(0.1, 0.1, 0.1);
}

Perla::~Perla()
{

}

//void Perla::init()
//{
//
//}
