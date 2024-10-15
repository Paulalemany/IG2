#pragma once

#include "Bloque.h"
#include "Muro.h"
#include "Perla.h"
#include "Heroe.h"
#include <vector>
#include <iostream> 
#include <fstream>
#include <OgreTrays.h>

using namespace std;

class Laberinto
{
public:

	//Constructora
	Laberinto(Ogre::SceneManager* scene, const string& mapa, OgreBites::TextBox* textB);

	void updateTextBox();

	/// Getters

	Heroe* getHero() { return sinbad; }

	int getBloque(Vector3 coord, int ini, int fin);

	// n = muro: 0 ; perla: 1 ; suelo: 2
	string getTexture(int n) {
		switch (n) {
		case 0:
			return texturaMuro;
			break;
		case 1:
			return texturaPerla;
			break;
		case 2:
			return texturaSuelo;
			break;
		default:
			cout << "No hay textura definida en el metodo Laberinto::getTexture()" << endl;
			break;
		}
	}

	string getTipoLuz() { return tipoLuz; }

protected:

	Ogre::SceneManager* Sm = nullptr;
	Ogre::Vector3 pos = Vector3(0, 0, 0);

	std::vector< Ogre::SceneNode*> nodes;
	int node;

	std::vector<Bloque*> bloques;
	Heroe* sinbad;
	
	// fichero
	int NumFilas = 0;
	int NumColumnas = 0;
	string texturaSuelo = "";
	string texturaMuro = "";
	string texturaPerla = "";
	string tipoLuz = "";
	string fila = "";

	// caja de informacion
	OgreBites::TextBox* lTextBox = nullptr;

};

