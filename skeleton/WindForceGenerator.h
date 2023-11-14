#pragma once
#include "ForceGenerator.h"
class WindForceGenerator : public ForceGenerator
{
protected:
	Vector3 windVel;
	float k1 = 0.3, k2 = 0.001;

public:
	WindForceGenerator(Vector3 windVel) : ForceGenerator() {
		this->windVel = windVel; 
	}
	virtual ~WindForceGenerator(){}
	void applyForce(Particle* p);
	void removeForce(Particle* p);
};

