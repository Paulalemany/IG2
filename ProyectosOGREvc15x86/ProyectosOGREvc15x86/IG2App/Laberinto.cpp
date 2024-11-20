#include "Laberinto.h"
#include "Heroe.h"

Laberinto::Laberinto(Ogre::SceneManager* scene, const string& mapa, OgreBites::TextBox* tb, SceneNode* camNode)
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

	gridSize = NumFilas * box;	//El tamaño del laberinto es el numero de filas (o columnas es un cuadrado) por la distancia entre bloques

	numPerlas = 0;
	won = false;
	lost = false;

	// "Pinta" el laberinto a partir del fichero
	node = 0;
	for (int i = 0; i < NumFilas; i++) {
		input >> fila;

		for (int j = 0; j < NumColumnas; j++) {
			pos = Vector3(-i * box, 0, -j * box);
			nodes.push_back(Sm->getRootSceneNode()->createChildSceneNode());

			if (fila[j] == 'x')
			{
				bloques.push_back(new Muro(pos, nodes[node], Sm, texturaMuro, false));
			}
			else if (fila[j] == 'o') 
			{
				string name = "par" + to_string(node);
				bloques.push_back(new Perla(pos, nodes[node], Sm, texturaPerla, true, name));
				numPerlas++;
			}
			else if (fila[j] == 'h') 
			{
				sinbad = new Heroe(pos, nodes[node], Sm, 3);

				nodes.push_back(Sm->getRootSceneNode()->createChildSceneNode());
				node++;

				string name = "par" + to_string(node);
				bloques.push_back(new Perla(pos, nodes[node], Sm, texturaPerla, true, name));
				numPerlas++;
			}
			else if (fila[j] == 'v') 
			{
				villanos.push_back(new Villano(pos, nodes[node], Sm, 0));

				nodes.push_back(Sm->getRootSceneNode()->createChildSceneNode());
				node++;

				string name = "par" + to_string(node);
				bloques.push_back(new Perla(pos, nodes[node], Sm, texturaPerla, true, name));
				numPerlas++;
			}
			else if (fila[j] == 'V') 
			{
				villanos.push_back(new Frankestein(pos, nodes[node], Sm, 1));

				//Cuando hay enemigos tambien hay bloques traspasables debajo
				nodes.push_back(Sm->getRootSceneNode()->createChildSceneNode());
				node++;

				string name = "par" + to_string(node);
				bloques.push_back(new Perla(pos, nodes[node], Sm, texturaPerla, true, name));
				numPerlas++;
			}
			node++;
		}
	}


	updateTextBox();

	sinbad->setLab(this);
	for (auto v : getVillains()) {
		v->setLab(this);
		v->setHeroe(sinbad);
	}

	configLight(scene);

	input.close();

	///-------SUELO-------------------------------------------------------------
	double seg = gridSize / 10;
	MeshManager::getSingleton().createPlane(
		"plane",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(Vector3::UNIT_Y, 0),                              // orientacion del plano mediante la normal
		gridSize, gridSize,                                     // anchura
		seg, seg,                           // numero de segmentos 
		true, 1,
		10, 10,                                                 // [!] veces que se repite la textura
		Vector3::UNIT_Z                                         // orientacion up 
	);

	Entity* planeEnt = Sm->createEntity("suelo", "plane");
	planeEnt->setMaterialName(getTexture(2));
	SceneNode* planeNode = Sm->getRootSceneNode()->createChildSceneNode("planeNode");
	planeNode->attachObject(planeEnt);

	double poslab = gridSize / 2;	//Ponemos el suelo en la mitad del laberinto
	double offset = box / 2;

	// para que cuadre con el laberinto:
	planeNode->setPosition(Vector3(-poslab + offset, -offset, -poslab + offset));

	///-----------CAMARA--------------------------------------------------------
	camNode->setPosition(-poslab, 2500, -poslab);

	///-----------SISTEMA DE PARTICULAS-----------------------------------------
	/*ParticleSystem* pSys = Sm->createParticleSystem("psSmoke", "smokeParticleSystem");
	SceneNode* mPSNode = Sm->getRootSceneNode()->createChildSceneNode();
	pSys->setEmitting(true);
	mPSNode->attachObject(pSys);*/
}

void Laberinto::updateTextBox()
{
	lTextBox->clearText();
	lTextBox->appendText("Lives: " + sinbad->getVidas() +
						 "\nPoints: " + sinbad->getPoints() );

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
}

void Laberinto::updateLightPos()
{
	int sX, sZ;
	sX = getHero()->getPosition().x;
	sZ = getHero()->getPosition().z;
	mLightNode->setPosition(Vector3(sX, 300, sZ));
}


Bloque* Laberinto::getBlock(Vector3 pos, int& id)
{
	return getBloque(pos, 0, bloques.size() - 1, id);
}

Bloque* Laberinto::getBloque(Vector3 coord, int ini, int fin, int& id) const
{
	// puede q el bloque no este
	if (coord == bloques[ini]->getPosition()) {
		id = ini;
		return bloques[ini];
	}
	else if (fin - ini == 1) {
		id = -1;
		return nullptr;
	}

	int mitad = (ini + fin) / 2;

	//Vamos para la izquierda (Es mas peque�a la que buscamos)
	//Cuando sean iguales en la x se compara en la z
	int x = bloques[mitad]->getPosition().x;
	if ( x < coord.x ) {

		return getBloque(coord, ini, mitad, id);
	}

	if (x == coord.x && bloques[mitad]->getPosition().z < coord.z) {
		return getBloque(coord, ini, mitad, id);
	}

	else {
		return getBloque(coord, mitad, fin, id);
	}
}

bool Laberinto::checkCollision()
{

	///Colision con la perla
	//Necesitamos tambien la caja de la perla
	int ID = 0;
	getBlock(sinbad->getPosition(), ID);
	
	//Si es nullptr es que ya no tiene perla
	if (ID != -1 && bloques[ID]->pearl()) {

		sinbad->getPearl();
		updateTextBox();	//Esto actualiza los puntos

		gottenPearl(ID);
	}

	///Colision con los enemigos
	bool colision = false;
	int i = 0;
	AxisAlignedBox villainBox;
	AxisAlignedBox HeroBox = sinbad->getAABB();

	//Recorremos el vector de villanos y vemos si interseca con el heroe
	while (!colision && i < villanos.size()) {
		villainBox = villanos[i]->getAABB();

		colision = HeroBox.intersects(villainBox);

		i++;
	}

	return colision;
}

void Laberinto::winCondition()
{
	int points = std::stoi(sinbad->getPoints());
	// cuidao! aqui suponemos q Heroe::pearlPunctuation es 10.
	if (numPerlas ==  points / 10 && !lost) {
		won = true;

		cout << "GAME WON" << endl;
	}
	
	int lives = std::stoi(sinbad->getVidas());
	if (lives <= 0 && !won) {
		lost = true;

		cout << "GAME LOST" << endl;
	}
}

void Laberinto::gottenPearl(int id)
{
	//Quitamos la imagen de la perla
	bloques[id]->removeEntity();
	bloques[id]->setPearl(false);
}


