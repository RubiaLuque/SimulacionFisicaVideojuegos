#pragma once
#include <iostream>
#include <vector>
#include "core.hpp"
#include "Data.h"
#include "ParticleGenerator.h"
#include "Particle.h"

using namespace std;
//Esta clase almacena las particulas creadas y las destruye a su debido tiempo
class ParticleSystem
{
private:
	vector<ParticleGenerator*> gens;
	vector<ForceGenerator*> forces;

	Data::GENERATORS g;
	Data::FORCES f = Data::NULLF;
	
	list<Particle*> particles;
	double elapsedTime;

	double windSphereRadius = 50;
public:
	ParticleSystem(Data::GENERATORS gen);
	void addForce(Data::FORCES f);
	virtual ~ParticleSystem();
	void update(double t);
	

	//cambia la propiedad alive de las particulas 
	inline void setAlive(Particle* p, bool alive) noexcept { p->alive = alive; }
};

