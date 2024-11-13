#pragma once

#include "OgreTimer.h"
#include "IG2Object.h"
#include <OgreTimer.h>

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

	// configura las animaciones
	void configAnims();

	//addKeyFrame (nodeAnimationTrack, giro, posición, más parámetros…);
	//void addKeyFrame(NodeAnimationTrack a, Ogre::Quaternion giro, Vector3 pos);

protected:

	// tiempo que dura la animacion
	Ogre::Timer* timer = nullptr;

	Ogre::SceneNode* camN = nullptr;

	// scene manager
	Ogre::SceneManager* sm = nullptr;

	// caja de informacion
	OgreBites::TextBox* iTextBox = nullptr;

	// luz
	Ogre::Light* light = nullptr;
	Ogre::SceneNode* mLightNode = nullptr;

	// entidades
	Ogre::SceneNode* sinbadNode = nullptr;
	Ogre::Entity* sinbadEnt;

	// Animation states for Sinbad
	Ogre::AnimationState* animationStateDance;
	Ogre::AnimationState* animationStateRunBase;
	Ogre::AnimationState* animationStateRunTop;

	// Flags to control the animations
	bool isDancing = false;
	bool isRunning = false;

};

