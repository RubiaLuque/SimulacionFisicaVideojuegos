#pragma once
#include "core.hpp"
#include <list>
#include "Particle.h"
#include "Firework.h"
#include "SolidRigid.h"
#include <cmath>
#include <random>
#include "Data.h"
using namespace std;

template <typename T>
class ParticleGenerator
{
protected:
	Vector3 meanPos, meanVel;

public:
	virtual ~ParticleGenerator() {};
	virtual list<T*> generateParticles(double t) = 0; //esto hace que la clase sea abstracta
	virtual T* createParticle(Vector3 pos, Vector3 vel) = 0;
	virtual void setGeneratorPos(Vector3 v) { meanPos = v; }
};