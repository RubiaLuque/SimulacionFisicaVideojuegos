#pragma once
#include "GaussianParticleGenerator.h"

class GaussianP : public GaussianParticleGenerator<Particle>
{
public:
	GaussianP(Vector3 meanPos, Vector3 meanVel, Vector3 stdDevPos, Vector3 stdDevVel,
		Data::GENERATORS g) :GaussianParticleGenerator(meanPos, meanVel, stdDevPos, stdDevVel, g) {

	}

	GaussianP(Vector3 meanPos, Vector3 meanVel, Vector3 stdDevPos, Vector3 stdDevVel,
		Data::GENERATORS g, PxPhysics* gPhysics, PxScene* gScene) : GaussianParticleGenerator(meanPos, meanVel, stdDevPos, stdDevVel,
			g, gPhysics, gScene) {}

	virtual Particle* createParticle(Vector3 pos, Vector3 vel) {
		if (g == Data::NIEBLA) {
			return new Particle(pos, vel, 0.26, 0.998, g);
		}
		else {
			return new Particle(pos, vel, 1.0, 0.998, g);
		}

	}
};

