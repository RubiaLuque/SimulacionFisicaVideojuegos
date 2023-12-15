#pragma once
#include "Render/Camera.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include "SolidRigidSystem.h"
#include <vector>
#include "Data.h"

using namespace std;
using namespace Data;

class SceneManager
{
private:
	//vector de proyectiles
	vector<Particle*> particles;
	//referencia a la camara
	Camera* cam;
	vector<ParticleSystem*> sys;
	vector<ParticleSystem*> forces;

	vector<SolidRigidSystem*> solidSys;
	vector<SolidRigidSystem*> solidForces;

	Firework* firework;
	ForceRegistry<Particle>* fr = new ForceRegistry<Particle>();
	ForceRegistry<SolidRigid>* sFr = new ForceRegistry<SolidRigid>();

	bool particleSys;
	bool fire;
	PxPhysics* gPhysics; 
	PxScene* gScene;

public:
	SceneManager(PxPhysics* gPhysics, PxScene* gScene);

	virtual ~SceneManager();

	//añade proyectiles al vector
	void addProjectile(PROJECTILE_TYPE type);

	//Crear sistemas de particulas o solidos rigidos
	void addParticleSystem(GENERATORS gen);
	void addSolidRigidSystem(GENERATORS gen);

	//Añade fuerzas a todos los sistemas
	void addForceToSystem(FORCES f);

	void addFirework();
	void update(double t);

	void generateSpring();
	void generateSlinky();
	void setK(int op);

	void generateBuoyancyWater();
	void generateBuoyancyMercury();

	//cambia la propiedad alive de las particulas 
	inline void setAlive(Particle* p, bool alive) { p->alive = alive; }
};

