#pragma once

#include "Bloque.h"

class Muro : public Bloque
{
public:

	Muro();

	Muro(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, string textura, bool pasable);

	//Pendiente
	~Muro();

	Entity* getPerla() override { return nullptr; };
protected:

};

