#pragma once
#include <iostream>
#include <vector>
#include "core.hpp"
#include "Data.h"
#include "ParticleGenerator.h"
#include "SolidRigid.h"
#include "ExplosionForceGenerator.h"
#include "ForceRegistry.h"

using namespace std;
class SolidRigidSystem
{
private:
	vector<ParticleGenerator<SolidRigid>*> gens;
	vector<ForceGenerator<SolidRigid>*> forces;

	ForceRegistry<SolidRigid>* fr = new ForceRegistry<SolidRigid>();
	Data::GENERATORS g;
	Data::FORCES f = Data::NULLF;
	ExplosionForceGenerator<SolidRigid>* e;
	vector<SolidRigid*> solids;
	double elapsedTime;

	PxPhysics* gPhysics; 
	PxScene* gScene;

public:
	SolidRigidSystem(PxPhysics* gPhysics, PxScene* gScene);
	virtual ~SolidRigidSystem();

	void addForce(Data::FORCES f);

	void update(double t);

	void generateSpring();
	void generateSlinky();
	void generateBuoyancyWater();
	void generateBuoyancyMercury();

	void setK(int op);

	//cambia la propiedad alive de las particulas 
	inline void setAlive(SolidRigid* s, bool alive) noexcept { s->alive = alive; }
};

