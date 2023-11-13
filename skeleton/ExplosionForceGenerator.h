#pragma once
#include "ForceGenerator.h"
class ExplosionForceGenerator : public ForceGenerator
{
private:

public:
	ExplosionForceGenerator();
	virtual ~ExplosionForceGenerator();

	void applyForce(Particle* p);
	void removeForce(Particle* p);
};

