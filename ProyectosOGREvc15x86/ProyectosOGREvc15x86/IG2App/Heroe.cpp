#include "Heroe.h"

Heroe::Heroe()
{

}

Heroe::Heroe(Vector3 initPos, SceneNode* node, SceneManager* sceneMng)
	: IG2Object(initPos, node, sceneMng)
{
	sinbad = mSM->createEntity("Sinbad.mesh");
	node->attachObject(sinbad);
	node->setScale(10, 10, 10);
	node->yaw(Ogre::Degree(180));

	Snode = node;
	dir = Vector3(0, 0, 0);
}

void Heroe::move(Vector3 newDir)
{
	if (dir != newDir) {	//Cambiamos la direccion del movimiento
		dir = newDir;
	}
}

void Heroe::frameRendered(const Ogre::FrameEvent& evt)
{
	IG2Object::move(dir);
}


