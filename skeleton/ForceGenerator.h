#pragma once
#include "Particle.h"
class ForceGenerator
{
private:
public:
	ForceGenerator() noexcept {};
	virtual ~ForceGenerator() {};
	virtual void applyForce(Particle* p) = 0;

};

