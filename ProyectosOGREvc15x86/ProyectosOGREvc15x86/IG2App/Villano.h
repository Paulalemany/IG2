#pragma once
#include "IG2Object.h"

#include <OgreTimer.h>

class Villano : public IG2Object
{
public:
	Villano();

	Villano(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);

	//void entityMovement(Vector3 newDir) override;


	/// Getters
	
	// (...)

private:

	Ogre::Entity* villano;

	// distancia entre A y heroe
	double distanciaEuclideaA;
	// distancia entre B y heroe
	double distanciaEuclideaB;

	// 0 para ogrehead,
	// 1 para personalizado
	int tipoVillano;

	// tiempo actual
	Ogre::Timer* actualTime;

	// tiempo en el que se persigue al heroe
	Ogre::Timer* attackTimer;

	//tiempo en el que se huye del heroe
	Ogre::Timer* avoidTimer;

	enum Estado {
		HUIDA,
		PERSEGUIR,
	};

	Estado estado;


};

