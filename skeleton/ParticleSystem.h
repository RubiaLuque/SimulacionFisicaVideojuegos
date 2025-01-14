#pragma once
#include <iostream>
#include <vector>
#include "core.hpp"
#include "Data.h"
#include "ParticleGenerator.h"
#include "ExplosionForceGenerator.h"
#include "ForceRegistry.h"

using namespace std;
//Esta clase almacena las particulas creadas y las destruye a su debido tiempo
class ParticleSystem
{
private:
	vector<ParticleGenerator<Particle>*> gens;
	vector<ForceGenerator<Particle>*> forces;

	GravityForceGenerator* gr = new GravityForceGenerator();
	ExplosionForceGenerator<Particle>* e;

	ForceRegistry<Particle>* fr = new ForceRegistry<Particle>();

	Data::GENERATORS g;
	Data::FORCES f = Data::NULLF;
	
	list<Particle*> particles;
	double elapsedTime;


	bool idle = false;
	PxPhysics* gPhysics; 
	PxScene* gScene;

public:
	ParticleSystem(Data::GENERATORS gen, PxPhysics* gPhysics, PxScene* gScene);
	void setGeneratorPos(Vector3 pos, Data::GENERATORS g);
	void setForcePos(Vector3 pos, Data::FORCES f);
	void addForce(Data::FORCES f, Vector3 pos);
	virtual ~ParticleSystem();
	void update(double t);

	void generateSpring();
	void generateSlinky();
	void generateBuoyancyWater();
	void generateBuoyancyMercury();

	void setK(int op);

	ExplosionForceGenerator<Particle>* getExplosion() { return e; }

	//cambia la propiedad alive de las particulas 
	inline void setAlive(Particle* p, bool alive) noexcept { p->alive = alive; }
};

