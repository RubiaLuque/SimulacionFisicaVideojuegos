#pragma once
#include "ForceGenerator.h"
#include "core.hpp"
//#include "Particle.h"
using namespace std;

class GravityForceGenerator : public ForceGenerator
{
private:
	Vector3 acc;
	const float g = -9.8;
public:
	GravityForceGenerator() : ForceGenerator() {};
	virtual ~GravityForceGenerator() {};
	void applyForce(Particle* p);
	void removeForce(Particle* p) {};
};
