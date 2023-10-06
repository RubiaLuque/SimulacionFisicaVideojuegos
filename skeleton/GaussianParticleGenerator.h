#pragma once
#include "ParticleGenerator.h"

class GaussianParticleGenerator : public ParticleGenerator
{
private: 
	Vector3 stdDevPos, stdDevVel;
	double stdDev_t;

public:

	GaussianParticleGenerator();
	~GaussianParticleGenerator();
	virtual list<Particle*> generateParticles();
};

