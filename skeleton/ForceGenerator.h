#pragma once
#include "Particle.h"
#include "SolidRigid.h"

template <typename T>
class ForceGenerator
{
private:
public:
	ForceGenerator() noexcept {};
	virtual ~ForceGenerator() {};
	virtual void updateForce(T* p, double t) {};
	virtual void removeForce(T* p) = 0;
	virtual void applyForceDin(T* p, double t) {};
	virtual double expandForce(double t) { return 0; };

};

