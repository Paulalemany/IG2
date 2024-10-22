#pragma once
#include "IG2Object.h"

class Villano : public IG2Object
{
public:
	Villano();

	Villano(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);

	void move(Vector3 newDir);

	void frameRendered(const Ogre::FrameEvent& evt) override;

	/// Getters
	
	// (...)

private:

	Ogre::Entity* villano;
	SceneNode* sNode;
	Vector3 dir;


	//Laberinto* lab;


};

