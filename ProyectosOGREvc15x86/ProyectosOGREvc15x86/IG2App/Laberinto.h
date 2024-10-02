#pragma once

#include "Muro.h"
#include "Perla.h"
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
		else cout << "Fichero abierto correctamente" << endl;
		
		//Construye el laberinto a partir del fichero
		input >> NumFilas;
		input >> NumColumnas;
		
		node = 0;

		for (int i = 0; i < NumFilas; i++)
		{
			input >> fila;

			for (int j = 0; j < NumColumnas; j++)
			{
				pos = Vector3(i * 100, j * 100, 0);

				if (fila[j] == 'x')
				{
					nodes.push_back(Sm->getRootSceneNode()->createChildSceneNode());

					muros.push_back(new Muro(pos, nodes[node], Sm));
				}
				else if (fila[j] == 'o')
				{
					nodes.push_back(Sm->getRootSceneNode()->createChildSceneNode());

					perlas.push_back(new Perla(pos, nodes[node], Sm));
				}
				node++;
				
			}
		}
		
		input.close();
	}

protected:

	Ogre::SceneManager* Sm = nullptr;
	Ogre::Vector3 pos = Vector3(0, 0, 0);

	std::vector< Ogre::SceneNode*> nodes;
	int node;

	std::vector<Muro*> muros;
	std::vector<Perla*> perlas;

	int NumFilas = 0;
	int NumColumnas = 0;
	string fila = "";

};

