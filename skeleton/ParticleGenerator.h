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
	virtual list<T*> generateParticles() = 0; //esto hace que la clase sea abstracta
};