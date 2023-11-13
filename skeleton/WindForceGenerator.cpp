#include "WindForceGenerator.h"

void WindForceGenerator::applyForce(Particle* p)
{
	if (p != nullptr) {
		p->setVel(k1*(windVel - p->getVel()));
		p->setWind(true);
	}
}

void WindForceGenerator::removeForce(Particle* p)
{
	if (p != nullptr) {
		//p->setVel((windVel + p->getVel())/k1);
		p->setWind(false);
	}
}
