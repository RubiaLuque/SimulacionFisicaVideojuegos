#pragma once
#include "ParticleGenerator.h"
#include <random>
#include <cmath>

using namespace std;
template <typename T>
class UniformParticleGenerator : public ParticleGenerator<T>
{
protected:
	Vector3 velWidth, posWidth;
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_real_distribution<float> dis;
	bool idle = false;
	Data::GENERATORS g;

	PxPhysics* gPhysics = nullptr; 
	PxScene* gScene = nullptr;

public:
	UniformParticleGenerator(Vector3 meanPos, Vector3 meanVel, Vector3 posWidth, Vector3 velWidth, Data::GENERATORS g);
	UniformParticleGenerator(Vector3 meanPos, Vector3 meanVel, Vector3 posWidth, Vector3 velWidth, 
		Data::GENERATORS g, PxPhysics* gPhysics, PxScene* gScene);
	~UniformParticleGenerator();

	list<T> generateParticles();
};

