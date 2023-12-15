#pragma once
#include "GaussianParticleGenerator.h"
class GaussianSR:public GaussianParticleGenerator<SolidRigid>
{
public:
	GaussianSR(Vector3 meanPos, Vector3 meanVel, Vector3 stdDevPos, Vector3 stdDevVel,
		Data::GENERATORS g) :GaussianParticleGenerator(meanPos, meanVel, stdDevPos, stdDevVel, g) {

	}

	GaussianSR(Vector3 meanPos, Vector3 meanVel, Vector3 stdDevPos, Vector3 stdDevVel,
		Data::GENERATORS g, PxPhysics* gPhysics, PxScene* gScene) : GaussianParticleGenerator( meanPos, meanVel, stdDevPos, stdDevVel,
		g, gPhysics, gScene) {}


	virtual SolidRigid* createParticle(Vector3 pos, Vector3 vel) {
		if (g == Data::NIEBLA) {
			return new SolidRigid(pos, vel, { 0,0,0 }, { 0,0,0,1 }, 1, 0.15, Data::DYNAMIC, gPhysics, gScene);
		}
		else {
			std::mt19937 gen;
			std::uniform_real_distribution<double> dis{ 0, 1 };
			return new SolidRigid(pos, vel, { 0,0,0 }, { (float)dis(gen), (float)dis(gen),(float)dis(gen),1}, 1, 0.15, Data::DYNAMIC, gPhysics, gScene);
		}

	}
};

