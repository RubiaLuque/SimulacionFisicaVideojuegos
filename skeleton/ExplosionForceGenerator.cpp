#include "ExplosionForceGenerator.h"

ExplosionForceGenerator::ExplosionForceGenerator(Vector3 explosionPos) : ForceGenerator()
{
	this->explosionPos = explosionPos;
	K = 500;
}

ExplosionForceGenerator::~ExplosionForceGenerator()
{

}

void ExplosionForceGenerator::applyForceDin(Particle* p, double t)
{
	if (p != nullptr) {
		double r = sqrt(pow(p->getPos().x - explosionPos.x, 2) + pow(p->getPos().y - explosionPos.y, 2)
			+ pow(p->getPos().z - explosionPos.z, 2));

		p->addForce(K/pow(r,2) * Vector3(p->getPos().x - explosionPos.x, p->getPos().y - explosionPos.y,
			p->getPos().z - explosionPos.z) * exp(-t/tau));
	}
}

double ExplosionForceGenerator::expandForce(Particle* p, double t) {
	return p->getVel().magnitude() * t;
}
