#include "Villano.h"

Villano::Villano()
{

}

Villano::Villano(Vector3 initPos, SceneNode* node, SceneManager* sceneMng)
	: IG2Object(initPos, node, sceneMng)
{
	villano = mSM->createEntity("ogrehead.mesh");
	node->attachObject(villano);

	node->yaw(Ogre::Degree(180));

	//actualTime->reset();

	estado = PERSEGUIR;

	//attackTimer->reset

	dir = Vector3(1, 0, 0);



}

void Villano::setDir(Vector3 newDir)
{
	if (dir != newDir) {	//Cambiamos la direccion del movimiento

		proxDir = newDir;
	}
}

void Villano::frameRendered(const Ogre::FrameEvent& evt)
{
	cout << "dir: " << dir << endl;

	IG2Object::entityMovement(dir);

	//setDir(Vector3(1, 0, 0));
	IG2Object::move(dir);
}



