#pragma once
#include "ForceGenerator.h"
class WindForceGenerator : public ForceGenerator
{
private:
	Vector3 windVel;
	float k1 = 1, k2;

public:
	WindForceGenerator(Vector3 windVel) : ForceGenerator() {
		this->windVel = windVel;
	}
	virtual ~WindForceGenerator(){}
	void applyForce(Particle* p);
	void removeForce(Particle* p);
};

