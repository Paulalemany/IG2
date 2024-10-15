#pragma once

#include "Bloque.h"


class Perla : public Bloque
{
public:

	Perla();

	Perla(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, bool pasable);

	//Pendiente
	~Perla();

	//void init() override;
protected:
	//Laberinto* lab = nullptr;

};

