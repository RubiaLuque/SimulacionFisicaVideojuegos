#pragma once
#include <iostream>
#include <vector>
#include "core.hpp"
#include "Data.h"
#include "ParticleGenerator.h"
#include "SolidRigid.h"
#include "ExplosionForceGenerator.h"
#include "ForceRegistry.h"
#include "Target.h"

using namespace std;
class SolidRigidSystem
{
private:
	vector<ParticleGenerator<SolidRigid>*> gens;
	vector<ForceGenerator<SolidRigid>*> forces;

	vector<ForceGenerator<Target>*> forcesT;

	ForceRegistry<SolidRigid>* fr = new ForceRegistry<SolidRigid>();
	ForceRegistry<Target>* frT = new ForceRegistry<Target>();

	Data::GENERATORS g;
	Data::FORCES f = Data::NULLF;
	ExplosionForceGenerator<SolidRigid>* e;
	vector<SolidRigid*> solids;
	double elapsedTime;

	PxPhysics* gPhysics; 
	PxScene* gScene;

public:
	SolidRigidSystem(Data::GENERATORS g, PxPhysics* gPhysics, PxScene* gScene);
	virtual ~SolidRigidSystem();

	void addForce(Data::FORCES f);

	void update(double t);

	void generateSpring();
	void generateSpringTargets(Target* t1, Target* t2);
	void generateSlinky();
	void generateBuoyancyWater();
	void generateBuoyancyMercury();

	void setK(int op);

	ExplosionForceGenerator<SolidRigid>* getExplosion() { return e; }

	//cambia la propiedad alive de las particulas 
	inline void setAlive(SolidRigid* s, bool alive) noexcept { s->alive = alive; }
};

