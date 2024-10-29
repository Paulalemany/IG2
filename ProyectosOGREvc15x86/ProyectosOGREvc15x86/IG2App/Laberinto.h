#pragma once

#include "Bloque.h"
#include "Muro.h"
#include "Perla.h"
#include "Heroe.h"
#include "Villano.h"

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

	// actualiza datos del textBox
	void updateTextBox();

	// crea la luz y settea su tipo
	void configLight(Ogre::SceneManager* s);
	// actualiza posicion del foco segun la posicion de sinbad
	void updateLightPos();

	/// Getters

	Heroe* getHero() { return sinbad; }

	Bloque* getBloque(Vector3 coord, int ini, int fin) const ;

	int getLenght() { return bloques.size(); }


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

	// Segun string del fichero devuelve el tipo de luz Ogre::Light::LightTypes. Default: directional.
	Ogre::Light::LightTypes getTipoLuz() { 
		if (tipoLuz == "spotlight")	return Ogre::Light::LT_SPOTLIGHT;
		else if (tipoLuz == "point") return Ogre::Light::LT_POINT;
		else return Ogre::Light::LT_DIRECTIONAL;
	}

	void checkColision();

protected:

	Ogre::SceneManager* Sm = nullptr;
	Ogre::Vector3 pos = Vector3(0, 0, 0);

	std::vector<Ogre::SceneNode*> nodes;
	int node;

	std::vector<Bloque*> bloques;
	Heroe* sinbad;
	Villano* villano;
	
	// fichero
	int NumFilas = 0;
	int NumColumnas = 0;
	string texturaSuelo = "";
	string texturaMuro = "";
	string texturaPerla = "";
	string tipoLuz = "";
	string fila = "";

	// luces
	Ogre::Light* light = nullptr;
	Ogre::SceneNode* mLightNode = nullptr;

	// caja de informacion
	OgreBites::TextBox* lTextBox = nullptr;

};