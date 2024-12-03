#pragma once

#include "IG2Object.h"
#include <OgreTimer.h>

class Heroe;

class Villano : public IG2Object
{
public:
	Villano();

	Villano(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, int tipo);

	void setDir(Vector3 newDir);

	void frameRendered(const Ogre::FrameEvent& evt) override;

	Vector3 calculateEuclideanDistance();

	bool cruce();	//Calcula si el villano está en un cruce y puede girar

	// Cambia el estado actual del villano segun el tiempo transcurrido
	void manageTime();

	/// Getters & Setters
	
	void setLab(Laberinto* l) { lab = l; }
	void setHeroe(Heroe* h) { heroe = h; }

protected:

	Ogre::Entity* villano;
	Vector3 boxSize = Vector3(56, 52, 48);

	// al que vamos a perseguir
	Heroe* heroe = nullptr;


	// -- ESTADOS --
	enum Estado {
		HUIDA,
		PERSEGUIR,
	};

	Estado estado;
	// -------------

	// -- TEMPORIZADOR --
	// - se inicia con new Ogre::Timer() en la constructora
	// - se resetea con timer->reset()
	// - timer->getMilliseconds() devuelve en ms el tiempo transcurrido
	Ogre::Timer* timer;

	// tiempo (en ms) en el que se mantendra el estado PERSEGUIR
	int followTime;

	// tiempo (en ms) en el que se mantendra el estado HUIDA
	int avoidTime;
	//------------------

	std::vector<Vector3> direcciones;
	std::vector<Vector3> posiblesDir;

	enum Tipo {
		NORMAL,
		FRANK
	};
};

