#pragma once
#include "IG2Object.h"

class Laberinto;

class Heroe : public IG2Object
{
public:
	Heroe();

	Heroe(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, int vidas);

	void move(Vector3 newDir);

	bool Centre();

	void frameRendered(const Ogre::FrameEvent& evt) override;

	/// Getters
	// devuelve en string el numero de vidas
	string getVidas() { return to_string(sVidas) ; }

	// devuelve si Sinbad esta en movimiento
	bool getIsMoving() { return isMoving; }

	///Setters

	void setLab(Laberinto* l) { lab = l; }

private:

	Ogre::Entity* sinbad;
	SceneNode* sNode;
	Vector3 dir; 
	Vector3 proxDir;

	Laberinto* lab;

	int sVidas;

	bool isMoving;

	void movement();
};

