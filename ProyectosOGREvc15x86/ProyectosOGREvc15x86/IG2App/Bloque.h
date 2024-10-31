#pragma once
#include "IG2Object.h"

class Bloque : public IG2Object
{
public:

	Bloque() {};

	Bloque(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, bool pasable)
		:IG2Object(initPos, node, sceneMng) {

		pos = initPos;
		traspasable = pasable;

		perla = pasable;	//Cuando se crean todos los bloques pasables tendran perlas
	};

	~Bloque() {};

	// Getters & Setters
	Vector3 getPosition() { return pos; }

	void setTraspasable(bool trasp) { traspasable = trasp; }
	bool getTraspasable() { return traspasable; }

	virtual Entity* getPerla() = 0;

	bool pearl() { return perla; }

	void setPearl(bool p) { perla = p; }

private:
	Vector3 pos;

	bool traspasable;
	bool perla;

};

