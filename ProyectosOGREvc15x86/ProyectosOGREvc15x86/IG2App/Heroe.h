#pragma once
#include "IG2Object.h"

class Heroe : public IG2Object
{
public:
	Heroe();

	Heroe(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);

	void init() override;
private:
	Ogre::Entity* sinbad;
};

