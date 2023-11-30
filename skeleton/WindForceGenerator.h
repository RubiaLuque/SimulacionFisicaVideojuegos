#pragma once
#include "ForceGenerator.h"
class WindForceGenerator : public ForceGenerator
{
protected:
	Vector3 windVel;
	float k1 = 0.1, k2 = 0.005;

public:
	WindForceGenerator(Vector3 windVel) : ForceGenerator() {
		this->windVel = windVel; 
	}
	virtual ~WindForceGenerator(){}
	void updateForce(Particle* p, double t);
	void removeForce(Particle* p);
};

