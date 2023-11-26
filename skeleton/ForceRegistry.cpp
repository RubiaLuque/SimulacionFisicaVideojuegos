#include "ForceRegistry.h"

void ForceRegistry::updateForces(double t)
{
	for (auto it = begin(); it != end(); ++it) {
		it->first->updateForce(it->second, t);
	}
}

void ForceRegistry::addRegistry(ForceGenerator* f, Particle* p)
{

}

void ForceRegistry::deleteParticleRegistry(Particle* p)
{

}
