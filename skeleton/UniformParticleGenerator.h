#pragma once
#include "ParticleGenerator.h"
#include <random>
#include <cmath>

using namespace std;

class UniformParticleGenerator : public ParticleGenerator
{
private:
	Vector3 velWidth, posWidth;
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_real_distribution<float> dis;
	Data::GENERATORS g;

public:
	UniformParticleGenerator(Vector3 meanPos, Vector3 meanVel, Vector3 posWidth, Vector3 velWidth, Data::GENERATORS g);
	~UniformParticleGenerator();

	virtual list<Particle*> generateParticles();
};

