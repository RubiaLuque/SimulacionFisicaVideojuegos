#include "WindForceGenerator.h"

void WindForceGenerator::applyForce(Particle* p)
{
	if (p != nullptr) {
		p->addForce(k1*(windVel - p->getVel()) + 
			k2*(windVel - p->getVel()).magnitude()* (windVel - p->getVel()));
	}
}

void WindForceGenerator::removeForce(Particle* p)
{
}