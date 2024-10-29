#pragma once

#include "Bloque.h"


class Perla : public Bloque
{
public:

	Perla();

	Perla(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, string textura, bool pasable);

	void GetPerl();

	//Pendiente
	~Perla();

	Entity* getPerla() override  { return perla; }

protected:
	Ogre::Entity* perla;

};

