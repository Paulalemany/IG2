#pragma once
#include "IG2Object.h"
#include "Laberinto.h"

class Heroe : public IG2Object
{
public:
	Heroe();

	Heroe(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, int vidas);

	void entityMovement(Vector3 newDir) override;

	void setDir(Vector3 newDir);


	void GetPerl();

	void frameRendered(const Ogre::FrameEvent& evt) override;

	/// Getters
	// devuelve en string el numero de vidas
	string getVidas() { return to_string(sVidas) ; }

	string getPoints() { return to_string(points); }

	// devuelve si Sinbad esta en movimiento
	bool getIsMoving() { return isMoving; }

	///Setters

	void setLab(Laberinto* l) { lab = l; }

private:

	Ogre::Entity* sinbad;

	int sVidas;

	int points;
	int perlpoints = 10;

	bool isMoving;

	//void movement();
};

