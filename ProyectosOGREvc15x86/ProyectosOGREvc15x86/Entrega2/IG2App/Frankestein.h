#pragma once
#include "Villano.h"

class Frankestein : public Villano
{
public:
	Frankestein();

	Frankestein(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, int tipo);

	void frameRendered(const Ogre::FrameEvent& evt) override;

protected:

	SceneNode* ObjectNode = nullptr;
	Timer* timer;
	const int time = 2500;
	int dir = -1;

	//Escalas de los objetos
	double NodeScale = 0.025;
	double PetScale = 0.1;
	double ArmaScale = 0.05;
	double PatScale = 0.005;

	///Nos guardamos los nodos de las cosas que queremos que roten
	//Los nudos de las cabezas
	SceneNode* Nnudo1;
	SceneNode* Nnudo2;

	//las bolas de las armas
	SceneNode* Nbola1_1;
	SceneNode* Nbola1_2;
	SceneNode* Nbola1_3;

	SceneNode* Nbola2_1;
	SceneNode* Nbola2_2;
	SceneNode* Nbola2_3;
};

