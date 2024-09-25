#pragma once

#include "Muro.h"
#include <vector>
#include <iostream> 
#include <fstream>
using namespace std;

class Laberinto
{
public:

	//Constructora
	Laberinto(Ogre::SceneManager* scene, const string& mapa) {
		Sm = scene;

		//Lee el fichero
		ifstream input;
		input.open(mapa);

		if (!input.is_open()) cout << "No se encuentra el fichero" << endl; 
		
		//Construye el laberinto a partir del fichero
		input >> NumFilas;
		input >> NumColumnas;

		for (int i = 0; i < NumFilas; i++) {
			input >> fila;
			for (int j = 0; j < NumColumnas; j++) {

				if (fila[j] == 'x') {
					nodes.push_back(Sm->getRootSceneNode()->createChildSceneNode());
					pos = Vector3(i * 100, j * 100, 0);
					muros.push_back(new Muro(pos, nodes[j], Sm));
				}
				else if (fila[j] == 'o') {

				}
				
			}
		}

		input.close();
	}

protected:

	Ogre::SceneManager* Sm = nullptr;
	Ogre::Vector3 pos = Vector3(0, 0, 0);
	std::vector< Ogre::SceneNode*> nodes;
	std::vector<Muro*> muros;

	int NumFilas = 0;
	int NumColumnas = 0;
	string fila = "";

};

