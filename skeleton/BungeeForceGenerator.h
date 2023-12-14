#pragma once
#include "SpringForceGenerator.h"
template <typename T>
class BungeeForceGenerator : public SpringForceGenerator<T>
{
private:
public:
	BungeeForceGenerator(int K, int x0, Particle* other) : SpringForceGenerator(K, x0, other) {};
	virtual ~BungeeForceGenerator();
	void updateForce(T p, double t);
};

