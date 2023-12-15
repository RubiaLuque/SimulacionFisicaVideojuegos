#pragma once
#include "UniformParticleGenerator.h"

class UniformSR : public UniformParticleGenerator<SolidRigid>
{
public:
	UniformSR(Vector3 meanPos, Vector3 meanVel, Vector3 posWidth, Vector3 velWidth,
		Data::GENERATORS g) : UniformParticleGenerator(meanPos, meanVel, posWidth, velWidth, g) {

	}

	UniformSR(Vector3 meanPos, Vector3 meanVel, Vector3 posWidth, Vector3 velWidth,
		Data::GENERATORS g, PxPhysics* gPhysics, PxScene* gScene) :UniformParticleGenerator(meanPos, meanVel, posWidth, velWidth,
		g, gPhysics, gScene){
	
	}

	virtual SolidRigid* createParticle(Vector3 pos, Vector3 vel) {
		std::mt19937 gen;
		std::uniform_real_distribution<double> dis{ 0, 1 };
		return new SolidRigid(pos, vel, { 0,0,0 }, {(float)dis(gen), (float)dis(gen), (float)dis(gen), 1}, 1, 1, Data::DYNAMIC, gPhysics, gScene);
	}
};

