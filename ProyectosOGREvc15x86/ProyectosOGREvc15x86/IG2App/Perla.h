#pragma once

#include "Bloque.h"
#include <OgreParticleSystem.h>


class Perla : public Bloque
{
public:

	Perla();

	Perla(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, string textura, bool pasable, string psName);

	void GetPerl();

	//Pendiente
	~Perla();

	Entity* getPerla() override  { return perla; }

protected:
	Ogre::Entity* perla;

	//HUMO PARA EL LABERINTO
	ParticleSystem* pSys = nullptr;

};

