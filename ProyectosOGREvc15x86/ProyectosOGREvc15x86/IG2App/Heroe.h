#pragma once
#include "IG2Object.h"

class Heroe : public IG2Object
{
public:
	Heroe();

	Heroe(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, int vidas);

	void move(Vector3 newDir);

	void frameRendered(const Ogre::FrameEvent& evt) override;

	/// Getters
	// devuelve en string el numero de vidas
	string getVidas() { return to_string(sVidas) ; }

private:

	Ogre::Entity* sinbad;
	SceneNode* sNode;
	Vector3 dir; 

	int sVidas;
};

