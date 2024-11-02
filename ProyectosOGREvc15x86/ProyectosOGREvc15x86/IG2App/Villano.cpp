#include "Villano.h"
#include "Heroe.h"

Villano::Villano()
{

}

Villano::Villano(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, int tipo)
	: IG2Object(initPos, node, sceneMng)
{
	if (tipo == NORMAL) {
		villano = mSM->createEntity("ogrehead.mesh");
		node->attachObject(villano);
		node->yaw(Ogre::Degree(180));
	}

	estado = PERSEGUIR;

	attackTimer = new Ogre::Timer(); // inicia el temporizador

	proxDir = Vector3(1, 0, 0);

	//Las cuatro direcciones a comprobar en cada cruce
	direcciones.push_back(Vector3(0, 0, -1));	//Arriba
	direcciones.push_back(Vector3(0, 0, 1));	//Abajo
	direcciones.push_back(Vector3(1, 0, 0));	//Derecha
	direcciones.push_back(Vector3(-1, 0, 0));	//Izquierda

}

void Villano::setDir(Vector3 newDir)
{
	if (dir != newDir) {	//Cambiamos la direccion del movimiento

		proxDir = newDir;
	}
}

void Villano::frameRendered(const Ogre::FrameEvent& evt)
{
	//Del IG2Object
	entityMovement(dir);

	move(dir);

	//Si estamos en el centro 
	//Y estamos en un cruce
	if (Centre() && cruce()) {

		//Comprobamos si es mas conveniente girar o seguir recto
		proxDir = calculateEuclideanDistance();

	}
	//cout << "dir: " << dir << endl;
	//cout << "proxdir: " << proxDir << endl;
	// - si esta en un cruce (dir == 0,0,0) se calculan las distancias euclideas y
	// setteamos setDir la direccion que minimice la distancia
		// va a ir en la unica posible (no puede volver atras)

	if (dir == Vector3(0, 0, 0)) {

		//proxDir = calculateEuclideanDistance();
		// no entiendo por que peta

		cout << "Se ha parado" << endl;

		//Aquí debe llegar cuando la direccion mas rapida es la actual
	}
	
}

Vector3 Villano::calculateEuclideanDistance()
{
	// h: posicion del bloque destino del heroe
	Vector3 h = heroe->getProxBlock()->getPosition();

	// saca dist entre a y h
	//Vector3 a = getProxBlock()->getPosition();
	Vector3 a, pd;


	if (posiblesDir.size() == 1) return posiblesDir[0];	//Si solo hay una direccion posible vamos en esa direccion

	//Vamos a hacer la primera por separado
	//Cogemos el bloque en la direccion que vamos a mirars
	Bloque* bl = lab->getBloque(mNode->getPosition() + (posiblesDir[0] * 100), 0, lab->getLenght() - 1);
	
	a = bl->getPosition();
	float distance = a.distance(h);
	pd = posiblesDir[0];

	

	for (int i = 1; i < posiblesDir.size(); i++) {
		//Comparamos distancias y nos quedamos con la mas pequeñas
		bl = lab->getBloque(mNode->getPosition() + (posiblesDir[i] * 100), 0, lab->getLenght() - 1);

		a = bl->getPosition();

		//Nos guardamos la direccion de la distancia menor
		if (distance > a.distance(h))
		{
			distance = a.distance(h);
			pd = posiblesDir[i];
		}
	}

	posiblesDir.clear();

	return pd;

}

bool Villano::cruce()
{
	bool cruce = false;
	//Comprobamos si estamos en un cruce

	for (int i = 0; i < direcciones.size(); i++) {

		//Solo cuenta como cruce si la direccion es distinta a la actual
		// No se puede dar media vuelta
		//Puede que no haga falta esta comprobacion
		//Estoy mirando en las 4 direcciones cuando no debería dar media vuelta

		if (direcciones[i] != -dir) {
			//Comprobamos el bloque siguiente en la direccion que toque
			Bloque* b = lab->getBloque(mNode->getPosition() + (direcciones[i] * 100), 0, lab->getLenght() - 1);

			//Si el bloque es traspasable lo añadimos y hacemos cruce a true
			if (b->getTraspasable()) {
				cruce = true;
				posiblesDir.push_back(direcciones[i]);
			}
		}
		
	}

	//Si es mayor a 1 estamos ante un cruce
	return posiblesDir.size() > 1;
}



