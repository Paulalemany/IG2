#pragma once
#include "IG2Object.h"
#include "Helice.h"

class Avion : public IG2Object
{
public:
	Avion(Vector3 initPos, Ogre::SceneNode* node, Ogre::SceneManager* sceneMng);

	void rotate();

private:
	SceneNode* h1Node = nullptr;
	SceneNode* h2Node = nullptr;
};

