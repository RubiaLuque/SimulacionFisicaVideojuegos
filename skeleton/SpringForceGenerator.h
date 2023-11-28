#pragma once
#include "ForceGenerator.h"

class SpringForceGenerator : public ForceGenerator
{
private:
	int K;
	Particle* other;
	int increment = 10;
	int decrement = -10;

public:
	SpringForceGenerator(int K, int x0, Particle* other);
	virtual ~SpringForceGenerator();
	void updateForce(Particle* p, double t);

	inline void increaseK() noexcept { K += increment; }
	inline void decreaseK() noexcept { K += decrement; }
};

