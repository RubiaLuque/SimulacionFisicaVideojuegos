#include "WindForceGenerator.h"

void WindForceGenerator::applyForce(Particle* p)
{
	if (p != nullptr)
		p->setVel(windVel - p->getVel());
}

void WindForceGenerator::removeForce(Particle* p)
{
	if (p != nullptr)
		p->setVel(windVel + p->getVel());
}
