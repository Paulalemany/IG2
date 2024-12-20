#pragma once

#include "OgreTimer.h"
#include "IG2Object.h"
#include <OgreParticleSystem.h>

#include <vector>
#include <iostream> 
#include <fstream>
#include <OgreTrays.h>

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreCameraMan.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <OgreEntity.h>
#include <OgreSkeletonInstance.h>
#include <OgreBone.h>
#include <OgreKeyFrame.h>
#include <sstream>


using namespace std;
using namespace Ogre;

class IntroScene : public OgreBites::InputListener
{
public:
	// Constructora
	IntroScene(Ogre::SceneManager* scene, OgreBites::TextBox* textB, Ogre::SceneNode* camNode);

	void frameRendered(const Ogre::FrameEvent& evt) override;


	// configura la caja de informacion
	void configTextBox();

	// crea y configura la luz
	void configLight();

	// pone el suelo a la escena
	void addGround();

	// configura la camara
	void configCamera();

	// configura las animaciones
	void configSinbadAnim();
	void configOgreheadAnim();

	void stop();

	//addKeyFrame (nodeAnimationTrack, giro, posici�n, m�s par�metros�);
	//void addKeyFrame(NodeAnimationTrack a, Ogre::Quaternion giro, Vector3 pos);

protected:

	// timer para hacer enable del baile, andares o espadas
	Ogre::Timer* timer = nullptr;

	int danceTime; // durStep[0] * 1000
	int swordsTime; // durStep[4] * 1000
	int movingTime; // durStep[7] * 1000

	// duracion de cada keyframe
	Ogre::Real sDurStep[9];	// sinbad
	Ogre::Real oDurStep[7]; // ogrehead

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
	Ogre::SceneNode* ogreheadNode = nullptr;
	Ogre::Entity* sinbadEnt;
	Ogre::Entity* ogreheadEnt;
	Ogre::Entity* swordLeftEnt;
	Ogre::Entity* swordRightEnt;

	// Flags to control the attached swords
	bool attachedLeftSword = false;
	bool attachedRightSword = false;

	// Animation states for Sinbad
	Ogre::AnimationState* animationStateDance;
	Ogre::AnimationState* animationStateRunBase;
	Ogre::AnimationState* animationStateRunTop;

	// Animation state
	Ogre::AnimationState* animationState;
	Ogre::AnimationState* ogreheadAnimationState;

	// Animation
	Ogre::Animation* sinbadAnim = nullptr;
	Ogre::Animation* ogreAnim = nullptr;

	// Flags to control the animations
	bool isDancing = false;
	bool isMoving = false;
	bool swordsAttached = false;
	bool _stop = false;


	///Sistema de particulas
	//Fuego
	std::vector<ParticleSystem*> fueguitos;
	std::vector<SceneNode*> nodes;
	Ogre::Vector3 pos {-120, 15, -100};	//POsicion del primer fuego que se genera

	//humillo
	ParticleSystem* humillo = nullptr;

};

