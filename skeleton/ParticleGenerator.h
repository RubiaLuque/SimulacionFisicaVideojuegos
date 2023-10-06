#pragma once
#include "core.hpp"
#include <list>
#include "Particle.h"

using namespace std;

class ParticleGenerator
{
private:
	string name;
	Vector3 meanPos, meanVel;
	double generationProb;
	int numParticles;
	Particle* model;

public:
	void setParticle(Particle* model);

	virtual list<Particle* > generateParticles() = 0; //esto hace que la clase sea abstracta
};

