#include "Heroe.h"

Heroe::Heroe()
{

}

Heroe::Heroe(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, int vidas)
	: IG2Object(initPos, node, sceneMng)
{
	sinbad = mSM->createEntity("Sinbad.mesh");
	node->attachObject(sinbad);
	node->setScale(10, 10, 10);
	node->yaw(Ogre::Degree(180));

	sVidas = vidas;

	isMoving = false;

	points = 0;

	timer = new Ogre::Timer();
	immunityTime = 3000;
	immune = false;
}

void Heroe::setDir(Vector3 newDir)
{
	if (dir != newDir) {	//Cambiamos la direccion del movimiento

		proxDir = newDir;
	}
}

void Heroe::entityMovement(Vector3 newDir)
{
	
	colision = lab->checkCollision();

	// Si colisiona con enemigo: resta vidas y pone inmunidad a true
	if (!immune && colision) {
		sVidas--;
		immune = true;
		cout << "INMUNE TRUE" << endl;

		timer->reset();
		colision = false;
	}

	// ^^^^ NO FUNCIONA BIEN
	// se deberia llamar solo cuando hay colision con villano,
	// una vez ha colisionado se mantiene llamando aqui,
	// a veces se llama sin colisionar con villano -> checkear el checkCollision

	lab->updateTextBox();

	if (Centre()) {
		//
		//// Si colisiona con enemigo: resta vidas y pone inmunidad a true
		//if (!immune) {
		//	sVidas--;
		//	immune = true;
		//	cout << "INMUNE TRUE" << endl;
		//	
		//	timer->reset();
		//}

		//// ^^^^ NO FUNCIONA BIEN
		//// se deberia llamar solo cuando hay colision con villano,
		//// una vez ha colisionado se mantiene llamando aqui,
		//// a veces se llama sin colisionar con villano -> checkear el checkCollision

		//lab->updateTextBox();
	}

	// para que llame al del padre (si no no lo llamaria)
	IG2Object::entityMovement(newDir);
}

void Heroe::getPearl()
{
	points += pearlPoints;
}


void Heroe::frameRendered(const Ogre::FrameEvent& evt)
{
	entityMovement(dir);

	IG2Object::move(dir);

	lab->updateLightPos();

	checkImmunity();

	//cout << timer->getMilliseconds() / 1000 << endl;
}

void Heroe::checkImmunity()
{
	// si es inmune y han pasado 3 segundos
	if (immune && timer->getMilliseconds() >= immunityTime) {
		// le quitamos inmunidad
		immune = false;

		cout << "INMUNE FALSE" << endl;
	}
}

