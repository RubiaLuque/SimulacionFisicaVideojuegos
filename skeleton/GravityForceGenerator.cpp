#include "GravityForceGenerator.h"

void GravityForceGenerator::updateForce(Particle* p, double t)
{
	p->addForce({ 0, (float)p->getMass() * g, 0 });
}
