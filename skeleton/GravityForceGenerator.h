#pragma once
#include "ForceGenerator.h"
#include "core.hpp"
//#include "Particle.h"
using namespace std;

class GravityForceGenerator : public ForceGenerator<Particle>
{
private:
	Vector3 acc;
	const float g = -10;
public:
	GravityForceGenerator() : ForceGenerator() {};
	virtual ~GravityForceGenerator() {};
	void updateForce(Particle* p, double t);
	void removeForce(Particle* p) {};
};

