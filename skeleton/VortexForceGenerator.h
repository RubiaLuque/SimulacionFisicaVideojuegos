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
	void updateForce(Particle* p, double t);
	void removeForce(Particle* p);
};

