#pragma once
#include "IG2Object.h"
#include "Laberinto.h"
#include "OgreTimer.h"

class Heroe : public IG2Object
{
public:
	Heroe();

	Heroe(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, int vidas);

	void entityMovement(Vector3 newDir) override;

	void setDir(Vector3 newDir);

	void getPearl();

	void frameRendered(const Ogre::FrameEvent& evt) override;

	void checkImmunity();

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
	int pearlPoints = 10;

	bool isMoving;

	// temporizador
	Ogre::Timer* timer;

	// tiempo (en ms) en el que sinbad no puede recibir daño
	int immunityTime;

	bool immune;
};

