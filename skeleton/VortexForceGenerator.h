#pragma once
#include "WindForceGenerator.h"
template <typename T>
class VortexForceGenerator : public WindForceGenerator<T>
{
private:
	int K;
	Vector3 vortexPos = { 0,0, 0 };

public:
	VortexForceGenerator(Vector3 windVel, Vector3 vortexPos);
	virtual ~VortexForceGenerator() {};
	void updateForce(T p, double t);
	void removeForce(T p);
};

