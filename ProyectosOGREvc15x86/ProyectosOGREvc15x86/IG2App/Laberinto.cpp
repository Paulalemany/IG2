#include "Laberinto.h"

Laberinto::Laberinto(Ogre::SceneManager* scene, const string& mapa, OgreBites::TextBox* tb)
{
	Sm = scene;
	lTextBox = tb;

	//Lee el fichero
	ifstream input;
	input.open(mapa);

	if (!input.is_open()) cout << "No se encuentra el fichero" << endl;
	else cout << "Fichero abierto correctamente" << endl;

	input >> NumFilas >> NumColumnas;
	input >> texturaPerla >> texturaMuro >> texturaSuelo >> tipoLuz;

	// "Pinta" el laberinto a partir del fichero
	node = 0; // Nosotras haciamos nodes[j], por eso solo se pintaba 1 fila. Necesitabamos un contador para los nodos.
	for (int i = 0; i < NumFilas; i++) {
		input >> fila;

		for (int j = 0; j < NumColumnas; j++) {
			pos = Vector3(-i * 100, 0, -j * 100);
			nodes.push_back(Sm->getRootSceneNode()->createChildSceneNode());

			if (fila[j] == 'x') {
				bloques.push_back(new Muro(pos, nodes[node], Sm, texturaMuro, false));
			}
			else if (fila[j] == 'o') {
				bloques.push_back(new Perla(pos, nodes[node], Sm, texturaPerla, true));
			}
			else if (fila[j] == 'h') {

				sinbad = new Heroe(pos, nodes[node], Sm, 3);
			}
			else if (fila[j] == 'v') {

				//villano = new Villano(pos, nodes[node], Sm, 3);
			}
			node++;
		}
	}

	updateTextBox();
	sinbad->setLab(this);

	configLight(scene);

	input.close();
}

void Laberinto::updateTextBox()
{
	lTextBox->clearText();
	lTextBox->appendText("Lives: " + sinbad->getVidas() +
						 "\nPoints: " ); // TODO 

	lTextBox->refitContents();
}

void Laberinto::configLight(Ogre::SceneManager* s)
{
	light = s->createLight("Luz");
	light->setDiffuseColour(0.75, 0.75, 0.75);

	mLightNode = s->getRootSceneNode()->createChildSceneNode("nLuz");
	mLightNode->attachObject(light);

	light->setType(getTipoLuz());

	if (getTipoLuz() == Ogre::Light::LT_SPOTLIGHT ||
		getTipoLuz() == Ogre::Light::LT_POINT)
	{
		mLightNode->setDirection(Ogre::Vector3(0, -1, 0));
		updateLightPos();
	}
	else {
		cout << "La luz es direccional" << endl;
	}
}

void Laberinto::updateLightPos()
{
	int sX, sZ;
	sX = getHero()->getPosition().x;
	sZ = getHero()->getPosition().z;
	mLightNode->setPosition(Vector3(sX, 300, sZ));
}

Bloque* Laberinto::getBloque(Vector3 coord, int ini, int fin) const
{
	// puede q el bloque no este
	if (coord == bloques[ini]->getPosition()) {
		return bloques[ini];
	}
	else if (fin - ini == 1) {
		return nullptr;
	}

	int mitad = (ini + fin) / 2;

	//Vamos para la izquierda (Es mas peque�a la que buscamos)
	//Cuando sean iguales en la x se compara en la z
	int x = bloques[mitad]->getPosition().x;
	if ( x < coord.x ) {

		return getBloque(coord, ini, mitad);
	}

	if (x == coord.x && bloques[mitad]->getPosition().z < coord.z) {
		return getBloque(coord, ini, mitad);
	}

	else {
		return getBloque(coord, mitad, fin);
	}
}


