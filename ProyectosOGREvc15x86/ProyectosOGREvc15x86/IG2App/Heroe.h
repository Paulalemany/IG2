#pragma once
#include "IG2Object.h"

class Heroe : public IG2Object
{
public:
	Heroe();

	Heroe(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);

	void move(Vector3 newDir);

	void frameRendered(const Ogre::FrameEvent& evt) override;

private:

	Ogre::Entity* sinbad;
	SceneNode* Snode;
	Vector3 dir; 
};

