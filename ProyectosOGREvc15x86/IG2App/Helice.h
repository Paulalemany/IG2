#pragma once
#include "Blade.h"

class Helice : public IG2Object
{
public:
	Helice(Vector3 initPos, Ogre::SceneNode* node, Ogre::SceneManager* sceneMng, int n, int r);
	//void yaw(const Radian& angle);

private:
	std::vector<Blade*> palas;
	std::vector<SceneNode*> nodos;

	Entity* rotor = nullptr;
};

