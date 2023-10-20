#pragma once
#include "core.hpp"
#include <list>
#include "Particle.h"
#include "Firework.h"
#include <cmath>
#include <random>
using namespace std;

class ParticleGenerator
{
private:
	Vector3 meanPos, meanVel;
	double generationProb;
	int numParticles;
	Particle* model;

public:
	void setParticle(Particle* model);

	virtual list<Particle* > generateParticles() = 0; //esto hace que la clase sea abstracta
};

