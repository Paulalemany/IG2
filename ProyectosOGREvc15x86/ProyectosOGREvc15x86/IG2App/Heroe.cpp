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
}

void Heroe::setDir(Vector3 newDir)
{
	if (dir != newDir) {	//Cambiamos la direccion del movimiento

		proxDir = newDir;
	}
}

void Heroe::entityMovement(Vector3 newDir)
{
	if (Centre()) lab->checkColision();

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
}

