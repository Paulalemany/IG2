#include "Blade.h"

Blade::Blade(Vector3 initPos, Ogre::SceneNode* node, Ogre::SceneManager* sceneMng)
	:IG2Object(initPos, node, sceneMng)
{
	Entity* aspa = sceneMng->createEntity("cube.mesh");
	node->attachObject(aspa);

	node->setScale(0.5, 5, 0.1);

	Entity* cabeza = sceneMng->createEntity("ogrehead.mesh");
	SceneNode* cabezaNode = node->createChildSceneNode();
	cabezaNode->attachObject(cabeza);
	cabezaNode->setScale(2, 0.25, 1);
	cabezaNode->setPosition(-20, 40, 100);
}
