#include "Villano.h"
#include "Heroe.h"

Villano::Villano()
{

}

Villano::Villano(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, int tipo)
	: IG2Object(initPos, node, sceneMng)
{
	if (tipo == NORMAL) {
		villano = mSM->createEntity("ogrehead.mesh");
		node->attachObject(villano);
		node->yaw(Ogre::Degree(180));

		AxisAlignedBox aab = villano->getBoundingBox();
		aab.scale(boxSize);
	}

	estado = PERSEGUIR;
	timer = new Ogre::Timer(); // inicia el temporizador

	followTime = 10000;
	avoidTime = 7000;

	proxDir = Vector3(1, 0, 0);

	//Las cuatro direcciones a comprobar en cada cruce
	direcciones.push_back(Vector3(0, 0, -1));	//Arriba
	direcciones.push_back(Vector3(0, 0, 1));	//Abajo
	direcciones.push_back(Vector3(1, 0, 0));	//Derecha
	direcciones.push_back(Vector3(-1, 0, 0));	//Izquierda
}

void Villano::setDir(Vector3 newDir)
{
	if (dir != newDir) {	//Cambiamos la direccion del movimiento

		proxDir = newDir;
	}
}

void Villano::frameRendered(const Ogre::FrameEvent& evt)
{
	//Del IG2Object
	entityMovement(dir);

	move(dir);

	//Si estamos en el centro //Calculamos para la siguiente iteracion pero bueno no se descuadra
	//Y estamos en un cruce
	if (Centre() && cruce()) {

		//Comprobamos si es mas conveniente girar o seguir recto
		proxDir = calculateEuclideanDistance();

	}

	manageTime();

}

Vector3 Villano::calculateEuclideanDistance()
{
	// h: posicion del bloque destino del heroe
	Vector3 h = heroe->getProxBlock()->getPosition();

	// a: saca dist entre a posicion siguiente optima
	// pd: proxima direccion a seguir por ahora
	Vector3 a, pd;

	//Vamos a hacer la primera por separado para tener algo con lo que comparar
	//Cogemos el bloque en la direccion que vamos a mirar
	int id = 0;
	Bloque* bl = lab->getBlock(mNode->getPosition() + (posiblesDir[0] * 100), id);
	
	//Calculamos la distancia
	a = bl->getPosition();
	float distance = a.distance(h);
	pd = posiblesDir[0];

	
	//Comparamos la calculada con el resto que haya
	for (int i = 1; i < posiblesDir.size(); i++) {
		//Comparamos distancias y nos quedamos con la mas pequeñas
		bl = lab->getBlock(mNode->getPosition() + (posiblesDir[i] * 100), id);

		a = bl->getPosition();

		if (estado == PERSEGUIR) {
			//Nos guardamos la direccion de la distancia menor
			if (distance > a.distance(h))
			{
				distance = a.distance(h);
				pd = posiblesDir[i];
			}
		}
		else {
			//Nos guardamos la direccion de la distancia mayor
			if (distance < a.distance(h))
			{
				distance = a.distance(h);
				pd = posiblesDir[i];
			}
		}
		
	}

	//Limpiamos el vector para que no se acumulen
	posiblesDir.clear();

	return pd;

}

//Comprobamos si estamos en un cruce
bool Villano::cruce()
{
	for (int i = 0; i < direcciones.size(); i++) {	//Comprobamos las 4 direcciones posibles

		//Solo cuenta como cruce si la direccion es distinta a la actual
		//No se puede dar media vuelta

		//Si la direccion que estamos mirando es la opuesta a la actual no es una opcion
		if (direcciones[i] != -dir) {	
			//Comprobamos el bloque siguiente en la direccion que toque
			int id = 0;
			Bloque* b = lab->getBlock(mNode->getPosition() + (direcciones[i] * 100), id);

			//Si el bloque es traspasable lo añadimos
			if (b->getTraspasable()) {
				posiblesDir.push_back(direcciones[i]);
			}
		}
		
	}

	//Si la unica direccion posible es la actual no estamos en un cruce
	//Si hay mas estamos en un cruce
	return posiblesDir.size() > 1;
}

void Villano::manageTime()
{
	if (estado == PERSEGUIR && timer->getMilliseconds() >= followTime) // cuando pasen 10 segundos pasaremos al estado de huida
	{
		estado = HUIDA;
		timer->reset();
	}
	else if (estado == HUIDA && timer->getMilliseconds() >= avoidTime) // cuando pasen 7 segundos pasaremos al estado de perseguir
	{
		estado = PERSEGUIR;
		timer->reset();
	}
}



