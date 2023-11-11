#include "GravityForceGenerator.h"

void GravityForceGenerator::applyForce(Particle* p)
{
	p->setAcc({ 0, (float)p->getMass() * g, 0 });
}
