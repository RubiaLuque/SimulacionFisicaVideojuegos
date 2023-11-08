#pragma once
#include "ForceGenerator.h"
#include "core.hpp"
#include "Particle.h"
using namespace std;

class GravityForceGenerator : public ForceGenerator
{
private:
	Vector3 acc;

public:
	GravityForceGenerator();
	virtual ~GravityForceGenerator();
	void applyForce(Particle* p);
};

