#pragma once

#include "Bloque.h"
#include "Laberinto.h"
class Laberinto;

class Muro : public Bloque
{
public:

	Muro();

	Muro(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, bool pasable);

	//Pendiente
	~Muro();

	//void init() override;
protected:
	//Laberinto* lab = nullptr;

};

