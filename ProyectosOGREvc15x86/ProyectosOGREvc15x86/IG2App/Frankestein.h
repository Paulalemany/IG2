#pragma once
#include "Villano.h"

class Frankestein : public Villano
{
public:
	Frankestein();

	Frankestein(Vector3 initPos, SceneNode* node, SceneManager* sceneMng);

	void frameRendered(const Ogre::FrameEvent& evt) override;

protected:
	SceneNode* ObjectNode = nullptr;

	double NodeScale = 0.025;
	double PetScale = 0.1;
	double ArmaScale = 0.05;
	double PatScale = 0.005;

	//Nos guardamos los nodos de las cosas que queremos que roten
	SceneNode* Nnudo1;
	SceneNode* Nnudo2;
};

