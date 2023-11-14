#include "ExplosionForceGenerator.h"

ExplosionForceGenerator::ExplosionForceGenerator()
{

}

void ExplosionForceGenerator::applyForceDin(Particle* p, double t)
{
	if (p != nullptr) {
		p->addForce();
	}
}
