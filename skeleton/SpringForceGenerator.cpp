#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(int K, int x0, Particle* other)
{
	this->K = K;
	this->other = other;
	this->x0 = x0;
}

SpringForceGenerator::~SpringForceGenerator()
{
	//delete other;
}

void SpringForceGenerator::updateForce(Particle* p, double t)
{
	if (p != nullptr) {
		Vector3 aux = other->getPos() - p->getPos();
		Vector3 force;

		const float length = aux.normalize();
		const float delta_x = length - x0;

		force = aux * delta_x * K;

		p->addForce(force);
	}
}
