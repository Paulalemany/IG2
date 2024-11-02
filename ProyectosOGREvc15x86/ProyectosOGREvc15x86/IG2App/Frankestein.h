#pragma once
#include "Villano.h"

class Frankestein : public Villano
{
public:
	Frankestein();

	Frankestein(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);

protected:
	SceneNode* ObjectNode = nullptr;

	double NodeScale = 0.025;
	double PetScale = 0.1;
	double ArmaScale = 0.05;
	double PatScale = 0.005;
};

