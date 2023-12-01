#pragma once
#include "SpringForceGenerator.h"
class BungeeForceGenerator : public SpringForceGenerator
{
private:
public:
	BungeeForceGenerator(int K, int x0, Particle* other) : SpringForceGenerator(K, x0, other) {};
	virtual ~BungeeForceGenerator();
	void updateForce(Particle* p, double t);
};

