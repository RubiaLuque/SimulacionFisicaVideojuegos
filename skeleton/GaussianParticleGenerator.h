#pragma once
#include "ParticleGenerator.h"
#include <random>
#include <cmath>

class normal_distribution;
template <typename T>
class GaussianParticleGenerator : public ParticleGenerator<T>
{
protected: 
	Vector3 stdDevPos, stdDevVel;

	double stdDev_t = 0.5;

	std::random_device rd;
	std::mt19937 gen;
	std::normal_distribution<float> d;

	Data::GENERATORS g;

	PxPhysics* gPhysics = nullptr; 
	PxScene* gScene = nullptr;

public:

	GaussianParticleGenerator(Vector3 meanPos, Vector3 meanVel, Vector3 stdDevPos, Vector3 stdDevVel, Data::GENERATORS g);
	GaussianParticleGenerator(Vector3 meanPos, Vector3 meanVel, Vector3 stdDevPos, Vector3 stdDevVel, 
		Data::GENERATORS g, PxPhysics* gPhysics, PxScene* gScene);
	~GaussianParticleGenerator();
	list<T> generateParticles();
};

