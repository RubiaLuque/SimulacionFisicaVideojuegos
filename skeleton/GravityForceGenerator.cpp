#include "GravityForceGenerator.h"

void GravityForceGenerator::applyForce(Particle* p)
{
	p->addForce({ 0, (float)p->getMass() * g, 0 });
}
