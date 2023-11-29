#pragma once
#include "ForceGenerator.h"

class BuoyancyForceGenerator : public ForceGenerator
{
private:
	float height;
	float volume;
	float density;
	float gravity = 9.8;

	Particle* liquid;

public:
	BuoyancyForceGenerator(float height, float volume, float density);
	virtual ~BuoyancyForceGenerator();
	void removeForce(Particle* p) {};

	void updateForce(Particle* p, double t);

};

