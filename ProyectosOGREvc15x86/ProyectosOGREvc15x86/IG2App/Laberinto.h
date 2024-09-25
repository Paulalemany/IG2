#pragma once

#include "Muro.h"
using namespace std;

class Laberinto
{
public:

	//Constructora
	Laberinto() {
		//Lee el fichero
		//Construye el laberinto a partir del fichero
		_muro = new Muro();
	}

protected:
	Muro* _muro = nullptr;
};

