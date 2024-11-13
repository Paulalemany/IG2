#pragma once

#include "OgreTimer.h"
#include "IG2Object.h"

#include <vector>
#include <iostream> 
#include <fstream>
#include <OgreTrays.h>

using namespace std;
using namespace Ogre;

class IntroScene
{
public:
	// Constructora
	IntroScene(Ogre::SceneManager* scene, OgreBites::TextBox* textB, Ogre::SceneNode* camNode);


	// configura la caja de informacion
	void configTextBox();

	// crea y configura la luz
	void configLight();

	// pone el suelo a la escena
	void addGround();

	// configura la camara
	void configCamera();

protected:

	Ogre::SceneNode* camN = nullptr;

	// scene manager
	Ogre::SceneManager* sm = nullptr;

	// caja de informacion
	OgreBites::TextBox* iTextBox = nullptr;

	// luz
	Ogre::Light* light = nullptr;
	Ogre::SceneNode* mLightNode = nullptr;

	//Enitidades
	Ogre::SceneNode* sinbadNode = nullptr;
	Ogre::Entity* sinbadEnt;
};

