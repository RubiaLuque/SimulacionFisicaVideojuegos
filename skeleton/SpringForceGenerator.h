#pragma once
#include "ForceGenerator.h"

class SpringForceGenerator : public ForceGenerator
{
protected:
	int K;
	int x0; //Longitud del muelle en reposo
	Particle* other;
	int increment = 10;
	int decrement = -10;

public:
	SpringForceGenerator(int K, int x0, Particle* other);
	virtual ~SpringForceGenerator();
	void updateForce(Particle* p, double t);
	void removeForce(Particle* p) {};
	inline void increaseK() noexcept { K += increment; }
	inline void decreaseK() noexcept { K += decrement; }
};

