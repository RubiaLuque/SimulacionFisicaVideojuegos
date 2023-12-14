#pragma once
#include "ForceGenerator.h"
template <typename T>
class BuoyancyForceGenerator : public ForceGenerator<T>
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
	void removeForce(T p) {};

	void updateForce(T p, double t);

};

