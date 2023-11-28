#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(int K, int x0, Particle* other)
{
	this->K = K;
	this->other = other;
}

SpringForceGenerator::~SpringForceGenerator()
{
	delete other;
}

void SpringForceGenerator::updateForce(Particle* p, double t)
{
	if (p != nullptr) {
		p->addForce(-K*(other->getPos() - p->getPos()));
	}
}
