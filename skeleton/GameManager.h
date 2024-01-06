#pragma once
#include "Render/Camera.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include "SolidRigidSystem.h"
#include "Target.h"
#include "Data.h"
#include "core.hpp"
#include "callbacks.hpp"
#include <PxPhysicsAPI.h>
#include "PxActor.h"
#include <vector>
using namespace std;
using namespace Data;

//Se encarga de gestionar la escena y su funcionamiento global
class GameManager
{
private:
	//Proyectiles de solidos rigidos y de particulas
	vector<SolidRigid*> projectiles;

	//Referencia a la camara
	Camera* cam;

	//Sistemas de particulas y de fuerzas
	vector<ParticleSystem*> sys;
	vector<ParticleSystem*> forces;

	//Sistemas de fuerzas de solidos rigidos
	vector<SolidRigidSystem*> solidForces;

	//Vector de dianas
	vector<Target*> targets;

	//Sistema fireworks
	Firework* firework;

	//Registros de fuerzas para particulas y solidos rigidos
	ForceRegistry<Particle>* fr = new ForceRegistry<Particle>();
	ForceRegistry<SolidRigid>* sFr = new ForceRegistry<SolidRigid>();

	//Elementos necesarios de physx para los solidos rigidos
	PxPhysics* gPhysics;
	PxScene* gScene;

	//Modo de juego
	GAME_MODE gm;

public:

	GameManager(PxPhysics* gPhysics, PxScene* gScene);
	virtual ~GameManager();

	void addProjectile(PROJECTILE_TYPE type);

	//Pantalla de eleccion de modo
	void chooseMode(char key);

	//Crear la distribucion inicial de las dianas y el modo de juego
	void setUpScene();

	//Configuraciones de los tres niveles de dificultad
	void easyMode();
	void mediumMode();
	void hardMode();

	//Actualizacion de los elementos de escena y de las colisiones
	void update(double t);

	//Colisiones 
	void onCollision(physx::PxActor* actor1, physx::PxActor* actor2);

	//Crea un firework al destruir una diana o ganar el juego
	void addFirework();

	//cambia la propiedad alive de las particulas 
	inline void setAlive(SolidRigid* p, bool alive) { p->alive = alive; }
	inline void setAlive(Target* p, bool alive) { p->alive = alive; }

};

