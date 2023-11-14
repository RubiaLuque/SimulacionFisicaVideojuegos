#pragma once
#include "ForceGenerator.h"
#include <cmath>
#include <numbers>

constexpr auto M_PI = 3.14159265358979323846;

class ExplosionForceGenerator : public ForceGenerator
{
private:
	int K;
	float tau = 2 * M_PI;
	Vector3 explosionPos;

public:
	ExplosionForceGenerator(Vector3 explosionPos);
	virtual ~ExplosionForceGenerator();

	void applyForce(Particle* p) {};
	void applyForceDin(Particle* p, double t);
	double expandForce(Particle* p, double t);
	void removeForce(Particle* p) {};
};

