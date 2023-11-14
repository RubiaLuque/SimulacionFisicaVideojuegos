#include "WindForceGenerator.h"

void WindForceGenerator::applyForce(Particle* p)
{
	if (p != nullptr) {
		p->addForce(k1*(windVel - p->getVel()));
		p->setWind(true);
	}
}

void WindForceGenerator::removeForce(Particle* p)
{
	if (p != nullptr) {
		p->setWind(false);
	}
}
