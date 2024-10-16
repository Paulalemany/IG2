#pragma once

#include "Bloque.h"
#include "Muro.h"
#include "Perla.h"
#include "Heroe.h"
#include <vector>
#include <iostream> 
#include <fstream>

using namespace std;

class Laberinto
{
public:

	//Constructora
	Laberinto(Ogre::SceneManager* scene, const string& mapa);

	Heroe* getHero() { return sinbad; }

	Bloque* getBloque(Vector3 coord, int ini, int fin);

	int GetCentre(Vector3 pos, int tam);

	int getLenght() { return bloques.size() - 1; }

protected:

	Ogre::SceneManager* Sm = nullptr;
	Ogre::Vector3 pos = Vector3(0, 0, 0);

	std::vector< Ogre::SceneNode*> nodes;
	int node;

	std::vector<Bloque*> bloques;
	Heroe* sinbad;
	

	int NumFilas = 0;
	int NumColumnas = 0;
	string fila = "";

};

