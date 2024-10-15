#include "Villano.h"

Villano::Villano()
{

}

Villano::Villano(Vector3 initPos, SceneNode* node, SceneManager* sceneMng)
	: IG2Object(initPos, node, sceneMng)
{
	villano = mSM->createEntity("ogrehead.mesh");
	node->attachObject(villano);
	node->setScale(10, 10, 10);
	node->yaw(Ogre::Degree(180));

	sNode = node;
	dir = Vector3(0, 0, 0);
}

void Villano::move(Vector3 newDir)
{
	if (dir != newDir) {	//Cambiamos la direccion del movimiento
		dir = newDir;

		//Rotacion
		Quaternion q = this->getOrientation().getRotationTo(newDir);
		sNode->rotate(q, Ogre::Node::TS_LOCAL);
	}
}

void Villano::frameRendered(const Ogre::FrameEvent& evt)
{
	IG2Object::move(dir);
}

