#pragma once
#include "Villano.h"

class Frankestein : public Villano
{
public:
	Frankestein();

	Frankestein(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);

protected:
	SceneNode* ObjectNode = nullptr;
};

