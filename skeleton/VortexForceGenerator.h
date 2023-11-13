#pragma once
#include "WindForceGenerator.h"
class VortexForceGenerator : public WindForceGenerator
{
private:
	int K;
	Vector3 vortexPos = { 0,0, 0 };

public:
	VortexForceGenerator(Vector3 windVel, Vector3 vortexPos);
	virtual ~VortexForceGenerator() {};
	void applyForce(Particle* p);
	void removeForce(Particle* p);
};

