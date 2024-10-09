#pragma once

#include "IG2Object.h"

class Bloque : public IG2Object
{
public:

	Bloque() {};

	Bloque(Vector3 initPos, SceneNode* node, SceneManager* sceneMng)
		:IG2Object(initPos, node, sceneMng) {

		pos = initPos;
		traspasable = true; // default: que se pueda traspasar
	};

	~Bloque() {};

	void setTraspasable(bool trasp) {
		traspasable = trasp;
	}

	bool getTraspasable() {
		return traspasable;
	}



private:
	Vector3 pos;

	bool traspasable;

};

