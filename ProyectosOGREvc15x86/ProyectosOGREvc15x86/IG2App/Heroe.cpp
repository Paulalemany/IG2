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
	immunityTime = 4000;
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

		timer->reset();
		colision = false;
	}

	lab->updateTextBox();

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

	lab->winCondition();
}

void Heroe::checkImmunity()
{
	// si es inmune y han pasado 4 segundos
	if (immune && timer->getMilliseconds() >= immunityTime) {
		// le quitamos inmunidad
		immune = false;

	}
}

