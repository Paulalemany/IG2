#include "Villano.h"
#include "Heroe.h"

Villano::Villano()
{

}

Villano::Villano(Vector3 initPos, SceneNode* node, SceneManager* sceneMng)
	: IG2Object(initPos, node, sceneMng)
{
	villano = mSM->createEntity("ogrehead.mesh");
	node->attachObject(villano);
	node->yaw(Ogre::Degree(180));

	estado = PERSEGUIR;

	attackTimer = new Ogre::Timer(); // inicia el temporizador

	proxDir = Vector3(1, 0, 0);

}

void Villano::setDir(Vector3 newDir)
{
	if (dir != newDir) {	//Cambiamos la direccion del movimiento

		proxDir = newDir;
	}
}

void Villano::frameRendered(const Ogre::FrameEvent& evt)
{
	//cout << "dir: " << dir << endl;
	cout << "proxdir: " << proxDir << endl;
	// - si esta en un cruce (dir == 0,0,0) se calculan las distancias euclideas y
	// setteamos setDir la direccion que minimice la distancia
		// va a ir en la unica posible (no puede volver atras)

	if (dir == Vector3(0,0,0)) {
		
		//proxDir = calculateEuclideanDistance();
		// no entiendo por que peta
	}

	//Del IG2Object
	entityMovement(dir);

	move(dir);

}

Vector3 Villano::calculateEuclideanDistance()
{
	// h: posicion del bloque destino del heroe
	Vector3 h = heroe->getProxBlock()->getPosition();

	Vector3 a, b;

	// direcciones posibles
	if (lastDir == Vector3(0, 0, -1) || lastDir == Vector3(0, 0, 1)) 
	{
		// la proxima sera o left o right

		proxDir = Vector3(1, 0, 0);
		a = getProxBlock()->getPosition();		
		
		proxDir = Vector3(-1, 0, 0);
		b = getProxBlock()->getPosition();
	}
	else if (lastDir == Vector3(1, 0, 0) || lastDir == Vector3(-1, 0, 0)) 
	{
		// la proxima sera o up o down
		proxDir = Vector3(0, 0, 1);
		a = getProxBlock()->getPosition();

		proxDir = Vector3(0, 0, -1);
		b = getProxBlock()->getPosition();
	}


	
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



