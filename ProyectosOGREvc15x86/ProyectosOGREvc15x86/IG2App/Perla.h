#pragma once

#include "Bloque.h"


class Perla : public Bloque
{
public:

	Perla();

	Perla(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, string textura, bool pasable);

	bool pearl() override { return perla; }


	//Pendiente
	~Perla();

	Entity* getPerla() override  { return _perla; }

protected:
	Ogre::Entity* _perla;

};

