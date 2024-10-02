#pragma once

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

protected:

	Ogre::SceneManager* Sm = nullptr;
	Ogre::Vector3 pos = Vector3(0, 0, 0);

	std::vector< Ogre::SceneNode*> nodes;
	int node;

	std::vector<Muro*> muros;
	std::vector<Perla*> perlas;
	Heroe* sinbad;
	

	int NumFilas = 0;
	int NumColumnas = 0;
	string fila = "";

};

