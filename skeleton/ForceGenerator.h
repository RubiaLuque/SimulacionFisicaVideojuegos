#pragma once
#include "Particle.h"
class ForceGenerator
{
private:
public:
	ForceGenerator() noexcept {};
	virtual ~ForceGenerator() {};
	virtual void updateForce(Particle* p, double t) {};
	virtual void applyForce(Particle* p) = 0;
	virtual void removeForce(Particle* p) = 0;
	virtual void applyForceDin(Particle* p, double t) {};
	virtual double expandForce(double t) { return 0; };

};

