#pragma once
#include "UniformParticleGenerator.h"

class UniformP : public UniformParticleGenerator<Particle>
{
public:
	UniformP(Vector3 meanPos, Vector3 meanVel, Vector3 posWidth, Vector3 velWidth,
		Data::GENERATORS g) : UniformParticleGenerator(meanPos, meanVel, posWidth, velWidth, g) {

	}

	UniformP(Vector3 meanPos, Vector3 meanVel, Vector3 posWidth, Vector3 velWidth,
		Data::GENERATORS g, PxPhysics* gPhysics, PxScene* gScene) :UniformParticleGenerator(meanPos, meanVel, posWidth, velWidth,
			g, gPhysics, gScene) {

	}

	virtual Particle* createParticle(Vector3 pos, Vector3 vel) {
		return new Particle(pos, vel, 1.0, 0.988, g);
	}
};

