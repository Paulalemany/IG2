#include "Heroe.h"
#include "Laberinto.h"

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

	sNode = node;
	dir = Vector3(0, 0, 0);
	proxDir = Vector3(0, 0, 0);


	sVidas = vidas;

	isMoving = false;
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
	x = sNode->getPosition().x;
	y = sNode->getPosition().y;
	z = sNode->getPosition().z;

	Vector3 centro(x % 100, y % 100, z % 100);
	
	//Si todos los numeros son multiplos de 100 esta en un centro
	return centro == Vector3().ZERO;	
}


void Heroe::frameRendered(const Ogre::FrameEvent& evt)
{

	movement();	//Gestiona el movimiento del heroe

	IG2Object::move(dir);

	lab->updateLightPos();

}

void Heroe::movement()
{
	//Si esta en el centro, la direccion debe cambiar, y el bloque es traspasable, giramos
	if (Centre() && dir != proxDir) {
		Bloque* b = lab->getBloque(sNode->getPosition() + (proxDir * 100), 0, lab->getLenght() - 1);

		if (b == nullptr || b->getTraspasable()) {
			dir = proxDir;

			Quaternion q = this->getOrientation().getRotationTo(dir);
			sNode->rotate(q, Ogre::Node::TS_LOCAL);
		}
	}

	//Si estamos en el centro y NO es traspasable hacemos dir = 0;

	if (Centre() && dir == proxDir) {

		Bloque* b = lab->getBloque(sNode->getPosition() + (dir * 100), 0, lab->getLenght() - 1);

		if (b != nullptr && b->getTraspasable() == false) {

			dir = Vector3(0, 0, 0);
			proxDir = Vector3(0, 0, 0);
		}
	}
}
