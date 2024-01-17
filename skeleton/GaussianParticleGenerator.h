#pragma once
#include "ParticleGenerator.h"
#include "GravityForceGenerator.h"
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

	float elapsedTime = 0;

public:

	GaussianParticleGenerator(Vector3 meanPos, Vector3 meanVel, Vector3 stdDevPos, Vector3 stdDevVel, 
		Data::GENERATORS g) : ParticleGenerator<T>()
	{
		std::random_device rd{};
		std::mt19937 gen{ rd() };
		d = std::normal_distribution<float>(0, stdDev_t);
		this->meanPos = meanPos;
		this->meanVel = meanVel;

		this->stdDevPos = stdDevPos;
		this->stdDevVel = stdDevVel;

		this->g = g;

	}

	GaussianParticleGenerator(Vector3 meanPos, Vector3 meanVel, Vector3 stdDevPos, Vector3 stdDevVel,
		Data::GENERATORS g, PxPhysics* gPhysics, PxScene* gScene) : ParticleGenerator<T>() {
		this->gScene = gScene;
		this->gPhysics = gPhysics;

		std::random_device rd{};
		std::mt19937 gen{ rd() };
		d = std::normal_distribution<float>(0, stdDev_t);
		this->meanPos = meanPos;
		this->meanVel = meanVel;

		this->stdDevPos = stdDevPos;
		this->stdDevVel = stdDevVel;

		this->g = g;
	}

	~GaussianParticleGenerator(){}

	virtual list<T*> generateParticles(double t) {
		GravityForceGenerator* gr = new GravityForceGenerator();
		list<T*> list;

		elapsedTime += t;
		if (elapsedTime >= Data::GENERATOR_TIME) {
			for (int i = 0; i < Data::TAM_LIST; ++i) {

				elapsedTime = 0;

				Vector3 auxPos = meanPos;
				auxPos.x += d(gen) * stdDevPos.x;
				auxPos.y += d(gen) * stdDevPos.y;
				auxPos.z += d(gen) * stdDevPos.z;

				Vector3 auxVel = meanVel;
				auxVel.x += d(gen) * stdDevVel.x;
				auxVel.y += d(gen) * stdDevVel.y;
				auxVel.z += d(gen) * stdDevVel.z;

				list.push_back(createParticle(auxPos, auxVel));

			}

		}



		return list;
	}
};

