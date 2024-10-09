#pragma once

#include "Bloque.h"

class Muro : public Bloque
{
public:

	Muro();

	Muro(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);

	//Pendiente
	~Muro();

	//void init() override;
protected:


};

