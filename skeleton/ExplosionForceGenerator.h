#pragma once
#include "ForceGenerator.h"
#include <cmath>
#include <numbers>


class ExplosionForceGenerator : public ForceGenerator
{
private:
	int K;
	float tau = 10000;
	Vector3 explosionPos;
	Vector3 expanseVel = { 340000,340000,340000 };
	double elapsedTime = 0;
	bool explosion = false;

public:
	ExplosionForceGenerator(Vector3 explosionPos);
	virtual ~ExplosionForceGenerator();

	void applyForce(Particle* p) {};
	void updateForce(Particle* p, double t) override;
	double expandForce(double t) override;
	void enableExplosion();
	void removeForce(Particle* p) {};
};

