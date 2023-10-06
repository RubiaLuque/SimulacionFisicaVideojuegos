#pragma once
#include "ParticleGenerator.h"

using namespace std;

class UniformParticleGenerator : public ParticleGenerator
{
private:
	Vector3 velWidth, posWidth;
public:
	UniformParticleGenerator();
	~UniformParticleGenerator();

	virtual list<Particle*> generateParticle();
};

