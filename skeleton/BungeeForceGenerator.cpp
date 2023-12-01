#include "BungeeForceGenerator.h"

void BungeeForceGenerator::updateForce(Particle* p, double t)
{
	Vector3 relPos = other->getPos() - p->getPos();
	if (relPos.magnitude() > x0) {
		SpringForceGenerator::updateForce(p, t);
	}
}
