#pragma once

#include "Bloque.h"
#include "Muro.h"
#include "Perla.h"
#include "Villano.h"
#include "Frankestein.h"

#include <vector>
#include <iostream> 
#include <fstream>
#include <OgreTrays.h>

using namespace std;

class Heroe;

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
	std::vector<Villano*> getVillains() const { return villanos; }

	Bloque* getBloque(Vector3 coord, int ini, int fin) const ;

	int getBloqueID(Vector3 coord, int ini, int fin) const;

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

	bool checkCollision();

	// Comprueba si Sinbad ha obtenido todas las perlas o ha perdido todas las vidas.
	// Pone win o lose a true dependiendo de que ocurra.
	void winCondition();

protected:

	//general
	Ogre::SceneManager* Sm = nullptr;
	Ogre::Vector3 pos = Vector3(0, 0, 0);
	int box = 100;	//Distancia que hay entre cajas

	//Enitidades
	int node;
	std::vector<Ogre::SceneNode*> nodes;
	std::vector<Bloque*> bloques;
	std::vector<Villano*> villanos;
	Heroe* sinbad;
	
	
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

	// contador de perlas en el laberinto
	int numPerlas;

	// se pone a true si consigue todas las perlas
	bool won;

	// se pone a false si pierde las vidas
	bool lost;

private:
	// perla recogida
	void gottenPearl(int id);

	// para el plano
	//size_t gridSize = 1800;
	size_t gridSize = 1900;	//Es el largo del laberinto

};