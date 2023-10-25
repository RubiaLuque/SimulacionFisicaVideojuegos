#pragma once
#include <list>
#include "core.hpp"
#include "Particle.h"
#include "Data.h"
#include "ParticleGenerator.h"
//#include "UniformParticleGenerator.h"
//#include "GaussianParticleGenerator.h"

using namespace std;
class UniformParticleGenerator;
class GaussianParticleGenerator;

class Firework
{
private:
	//almacena las particulas generadas
	list<Particle*> gens;
	UniformParticleGenerator* unif;
	GaussianParticleGenerator* normal;

	//posicion y velocidad base de la particula inicial
	Vector3 iniPos = { 0,0,0 };
	Vector3 iniVel = { 1, 20, 1 };

	//repertorio de particulas base
	Particle* p1;
	Particle* p2;
	Particle* p3;

public:
	Firework();
	virtual ~Firework();
	int update(double t);
	void shootParticle();
	list<Particle*> explode();
};

