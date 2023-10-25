#pragma once
#include "core.hpp"
#include <list>
#include "Particle.h"
#include "Firework.h"
#include <cmath>
#include <random>
#include "Data.h"
using namespace std;

class ParticleGenerator
{
protected:
	Vector3 meanPos, meanVel;
	Particle* model;

public:
	virtual ~ParticleGenerator() {};
	virtual list<Particle* > generateParticles() = 0; //esto hace que la clase sea abstracta
};