#include "Villano.h"

Villano::Villano()
{

}

Villano::Villano(Vector3 initPos, SceneNode* node, SceneManager* sceneMng)
	: IG2Object(initPos, node, sceneMng)
{
	/*villano = mSM->createEntity("ogrehead.mesh");
	node->attachObject(villano);

	node->yaw(Ogre::Degree(180));

	dir = Vector3(0, 0, 0);

	//actualTime->reset();

	estado = PERSEGUIR;

	//attackTimer->reset();
}

//void Villano::entityMovement(Vector3 newDir)
//{
//	// - Nunca cambia de sentido
//	// Calcula direccion si:
//	// - esta bloqueado
//	// - esta en posicion donde es posible hacer giro de 90 grados y avanzar
//	// 
//	// Direccion tomada: minimice distancia euclidea entre heroe y el centro del primer bloque visitado por el villano
//	//
//
//	//Si est� en el centro comprobamos las cosas
//	
//	// IG2Object::entityMovement(newDir);
//}


