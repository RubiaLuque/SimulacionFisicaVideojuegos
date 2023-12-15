#pragma once
#include "ParticleGenerator.h"
#include "GravityForceGenerator.h"
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
	UniformParticleGenerator(Vector3 meanPos, Vector3 meanVel, Vector3 posWidth, Vector3 velWidth, 
		Data::GENERATORS g) : ParticleGenerator<T>()
	{
		//de donde se parte
		this->meanPos = meanPos;
		this->meanVel = meanVel;

		//tipo de generador
		this->g = g;

		//distribucion
		std::random_device rd;
		std::mt19937 gen(rd());
		dis = std::uniform_real_distribution<float>(1.0, 2.0);

		this->posWidth = posWidth;
		this->velWidth = velWidth;
	}

	UniformParticleGenerator(Vector3 meanPos, Vector3 meanVel, Vector3 posWidth, Vector3 velWidth,
		Data::GENERATORS g, PxPhysics* gPhysics, PxScene* gScene) : ParticleGenerator<T>() {
		this->gPhysics = gPhysics;
		this->gScene = gScene;
		//de donde se parte
		this->meanPos = meanPos;
		this->meanVel = meanVel;

		//tipo de generador
		this->g = g;

		//distribucion
		std::random_device rd;
		std::mt19937 gen(rd());
		dis = std::uniform_real_distribution<float>(1.0, 2.0);

		this->posWidth = posWidth;
		this->velWidth = velWidth;
	}

	~UniformParticleGenerator(){}

	list<T*> generateParticles() {
		GravityForceGenerator* gr = new GravityForceGenerator();

		list<T*> list{};

		for (int i = 0; i < Data::TAM_LIST; ++i) {
			Vector3 auxPos = meanPos;
			auxPos.x += dis(gen) * posWidth.x;
			auxPos.y += dis(gen) * posWidth.y;
			auxPos.z += dis(gen) * posWidth.z;

			Vector3 auxVel = meanVel;
			auxVel.x += dis(gen) * velWidth.x;
			auxVel.y += dis(gen) * velWidth.y;
			auxVel.z += dis(gen) * velWidth.z;

			if (typeid(T) == typeid(Particle)) {
				auto p = new Particle(auxPos, auxVel, 1.0, 0.988, g);
				list.push_back(p);

			}
			else if (typeid(T) == typeid(SolidRigid)) {
				auto s = new SolidRigid(auxPos, auxVel, { 0,0,0 }, { 0.5, 0.5, 0.5, 1 }, Data::DYNAMIC);
				list.push_back(s);
			}
		}

		return list;
	}
};

