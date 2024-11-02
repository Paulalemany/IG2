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
		calculateEuclideanDistance();
		
	}
	//cout << "dir: " << dir << endl;
	cout << "proxdir: " << proxDir << endl;
	// - si esta en un cruce (dir == 0,0,0) se calculan las distancias euclideas y
	// setteamos setDir la direccion que minimice la distancia
		// va a ir en la unica posible (no puede volver atras)

	if (dir == Vector3(0,0,0)) {
		
		//proxDir = calculateEuclideanDistance();
		// no entiendo por que peta
	}
}

Vector3 Villano::calculateEuclideanDistance()
{
	// h: posicion del bloque destino del heroe
	Bloque* bl = heroe->getProxBlock();
	Vector3 h = Vector3(0, 0, 0);

	if (bl != nullptr) h = bl->getPosition();
	else h = heroe->getPosition();
	

	//Posibles direcciones (Dependerá de cuantas direcciones se hayan guardado
	Vector3 a, b;

	if (posiblesDir.size() == 1) return posiblesDir[0];	//Si solo hay una direccion posible vamos en esa direccion

	//Vamos a hacer la primera por separado
	

	for (int i = 0; i < posiblesDir.size(); i++) {


		//Comparamos distancias y nos quedamos con la mas pequeñas
		//float distance = b.distance(h);
	}

	//// direcciones posibles
	//if (lastDir == Vector3(0, 0, -1) || lastDir == Vector3(0, 0, 1)) 
	//{
	//	// la proxima sera o left o right

	//	proxDir = Vector3(1, 0, 0);
	//	a = getProxBlock()->getPosition();		
	//	
	//	proxDir = Vector3(-1, 0, 0);
	//	b = getProxBlock()->getPosition();
	//}
	//else if (lastDir == Vector3(1, 0, 0) || lastDir == Vector3(-1, 0, 0)) 
	//{
	//	// la proxima sera o up o down
	//	proxDir = Vector3(0, 0, 1);
	//	a = getProxBlock()->getPosition();

	//	proxDir = Vector3(0, 0, -1);
	//	b = getProxBlock()->getPosition();
	//}


	
	// dist entre a y h
	float ah = a.distance(h);
	// dist entre b y h
	float bh = b.distance(h);

	// comparar cual es menor
	//if(ah < bh) hacia ah
	// else hacia bh
		
	// xh es menor ->
	// la proxima direccion del villano sera hacia x

	// 	Vector3 direction;
	// ...

	// TO DO

	return Vector3();
}

bool Villano::cruce()
{
	bool cruce = false;
	//Comprobamos si estamos en un cruce

	for (int i = 0; i < direcciones.size(); i++) {

		//Solo cuenta como cruce si la direccion es distinta a la actual
		//Puede que no haga falta esta comprobacion
		if (direcciones[i] != dir) {	
			//Comprobamos el bloque siguiente en la direccion que toque
			Bloque* b = lab->getBloque(mNode->getPosition() + (direcciones[i] * 100), 0, lab->getLenght() - 1);

			//Si el bloque es traspasable lo añadimos y hacemos cruce a true
			if (b->getTraspasable()) {
				cruce = true;
				posiblesDir.push_back(direcciones[i]);
			}
		}
	}
	return cruce;
}



