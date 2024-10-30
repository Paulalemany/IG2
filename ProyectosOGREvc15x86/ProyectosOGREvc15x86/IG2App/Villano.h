#pragma once
#include "IG2Object.h"

#include <OgreTimer.h>

class Villano : public IG2Object
{
public:
	Villano();

	Villano(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);

	// - Nunca cambia de sentido
	// Calcula direccion si:
	// - esta bloqueado
	// - esta en posicion donde es posible hacer giro de 90 grados y avanzar
	// 
	// Direccion tomada: minimice distancia euclidea entre heroe y el centro del primer bloque visitado por el villano
	
	//void entityMovement(Vector3 newDir) override;

	void setDir(Vector3 newDir);

	void frameRendered(const Ogre::FrameEvent& evt) override;

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

