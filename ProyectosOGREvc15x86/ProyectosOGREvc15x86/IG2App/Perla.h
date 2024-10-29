#pragma once

#include "Bloque.h"


class Perla : public Bloque
{
public:

	Perla();

	Perla(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, string textura, bool pasable);

	//Pendiente
	~Perla();

	Entity* getPerla() override  { return perla; }

protected:
	Ogre::Entity* perla;

};

