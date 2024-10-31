#include "Villano.h"
#include "Heroe.h"

Villano::Villano()
{

}

Villano::Villano(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, Heroe* h)
	: IG2Object(initPos, node, sceneMng)
{
	villano = mSM->createEntity("ogrehead.mesh");
	node->attachObject(villano);
	node->yaw(Ogre::Degree(180));

	heroe = h;

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

	// - si esta en un cruce (dir == 0,0,0) se calculan las distancias euclideas y
	// setteamos setDir la direccion que minimice la distancia
		// va a ir en la unica posible (no puede volver atras)



	// --- proxDir sera distinta a dir que llevaba antes (dir = lastDir)

	if (dir == Vector3(0,0,0)) {
		
		
	}


	IG2Object::entityMovement(dir);

	IG2Object::move(dir);
}

Vector3 Villano::calculateEuclideanDistance()
{
	// h: posicion del bloque destino del heroe
	//Vector3 h = heroe->getProxBlock()->getPosition();

	// saca dist entre a y h
	//Vector3 a = getProxBlock()->getPosition();

	// saca dist entre b y h 
	//Vector3 b = getProxBlock()->getPosition();

	
	// dist entre a y h
	//float ah = a.distance(h);
	// dist entre b y h
	//float bh = b.distance(h);

	// comparar cual es menor
	//if(ah < bh) hacia ah
	// else hacia bh
		
	// xh es menor ->
	// la proxima direccion del villano sera hacia x

	// 	Vector3 direction;
	// ...


	return Vector3();
}



