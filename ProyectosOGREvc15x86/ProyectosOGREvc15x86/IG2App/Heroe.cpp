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
	proxDir = Vector3(0, 0, 0);

}

void Heroe::move(Vector3 newDir)
{
	if (dir != newDir) {	//Cambiamos la direccion del movimiento

		proxDir = newDir;
	}
}

bool Heroe::Centre()
{
	int x, y, z;
	x = Snode->getPosition().x;
	y = Snode->getPosition().y;
	z = Snode->getPosition().z;

	Vector3 centro(x % 100, y % 100, z % 100);
	
	//Si todos los numeros son multiplos de 100 esta en un centro
	return centro == Vector3().ZERO;	
}


void Heroe::frameRendered(const Ogre::FrameEvent& evt)
{
	//Falta comprobar si el bloque es un muro
	if (Centre() && dir != proxDir) {

		dir = proxDir;

		Quaternion q = this->getOrientation().getRotationTo(dir);
		Snode->rotate(q, Ogre::Node::TS_LOCAL);
	}

	IG2Object::move(dir);
}


