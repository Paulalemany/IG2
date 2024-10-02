#pragma once

#include "IG2Object.h"

class Perla : public IG2Object
{
public:

	Perla();

	Perla(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);

	//Pendiente
	~Perla();

	void init() override;
protected:


};

