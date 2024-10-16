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
			node++;
		}
	}

	updateTextBox();

	input.close();
}

void Laberinto::updateTextBox()
{
	lTextBox->clearText();
	lTextBox->appendText("Lives: " + sinbad->getVidas() +
						 "\nPoints: " ); // TODO 

	lTextBox->refitContents();
}

Bloque* Laberinto::getBloque(Vector3 coord, int ini, int fin)
{
	// puede q el bloque no este
	if (coord == bloques[ini]->getPosition()) {
		return bloques[ini];
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


