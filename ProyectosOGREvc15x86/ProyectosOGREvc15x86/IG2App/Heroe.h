#pragma once
#include "IG2Object.h"
//#include "Laberinto.h"

class Heroe : public IG2Object
{
public:
	Heroe();

	Heroe(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);

	void move(Vector3 newDir);

	bool Centre();

	void frameRendered(const Ogre::FrameEvent& evt) override;

	//void setLab(Laberinto* l) {lab = l; } 

private:

	Ogre::Entity* sinbad;
	SceneNode* Snode;
	Vector3 dir; 
	Vector3 proxDir;

	//Laberinto* lab;
};

