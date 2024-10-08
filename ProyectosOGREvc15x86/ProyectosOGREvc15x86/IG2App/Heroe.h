#pragma once
#include "IG2Object.h"

class Heroe : public IG2Object
{
public:
	Heroe();

	Heroe(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);

	void move(Vector3 dir);

private:
	Ogre::Entity* sinbad;
	SceneNode* Snode;
};

