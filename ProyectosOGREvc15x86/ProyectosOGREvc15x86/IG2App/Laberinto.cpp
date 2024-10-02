#include "Laberinto.h"

Laberinto::Laberinto(Ogre::SceneManager* scene, const string& mapa)
{
	Sm = scene;

	//Lee el fichero
	ifstream input;
	input.open(mapa);

	if (!input.is_open()) cout << "No se encuentra el fichero" << endl;
	else cout << "Fichero abierto correctamente" << endl;

	input >> NumFilas >> NumColumnas;

	// "Pinta" el laberinto a partir del fichero
	node = 0; // Nosotras haciamos nodes[j], por eso solo se pintaba 1 fila. Necesitabamos un contador para los nodos.
	for (int i = 0; i < NumFilas; i++) {
		input >> fila;

		for (int j = 0; j < NumColumnas; j++) {
			pos = Vector3(-i * 100, 0, - j * 100);
			nodes.push_back(Sm->getRootSceneNode()->createChildSceneNode());

			if (fila[j] == 'x') {
				muros.push_back(new Muro(pos, nodes[node], Sm));
			}
			else if (fila[j] == 'o') {
				perlas.push_back(new Perla(pos, nodes[node], Sm));
			}
			else if (fila[j] == 'h') {
				sinbad = new Heroe(pos, nodes[node], Sm);
			}
			node++;
		}
	}

	input.close();
}


