#pragma once
#include "WindForceGenerator.h"
class VortexForceGenerator : public WindForceGenerator
{
private:
	int K;
	Vector2 vortexPos = { 0,0 };

public:
	VortexForceGenerator(Vector3 windVel, Vector2 vortexPos);
	virtual ~VortexForceGenerator() {};
	void applyForce(Particle* p);
	void removeForce(Particle* p);
};

