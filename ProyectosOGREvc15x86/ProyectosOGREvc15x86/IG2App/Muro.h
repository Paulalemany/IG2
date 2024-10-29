#pragma once

#include "Bloque.h"
#include "Laberinto.h"
class Laberinto;

class Muro : public Bloque
{
public:

	Muro();

	Muro(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, string textura, bool pasable);

	//Pendiente
	~Muro();

	Entity* getPerla() override { return nullptr; };
protected:
	//Laberinto* lab = nullptr;

};

