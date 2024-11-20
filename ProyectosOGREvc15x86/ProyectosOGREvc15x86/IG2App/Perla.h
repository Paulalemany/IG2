#pragma once

#include "Bloque.h"
#include <OgreParticleSystem.h>


class Perla : public Bloque
{
public:

	Perla();

	Perla(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, string textura, bool pasable, string psName);

	bool pearl() override { return perla; }


	//Pendiente
	~Perla();

	Entity* getPerla() override  { return _perla; }

protected:
	Ogre::Entity* _perla;

	//HUMO PARA EL LABERINTO
	ParticleSystem* pSys = nullptr;

};

