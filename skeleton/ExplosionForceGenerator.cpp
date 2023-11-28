#include "ExplosionForceGenerator.h"
#include <iostream>
ExplosionForceGenerator::ExplosionForceGenerator(Vector3 explosionPos) : ForceGenerator()
{
	this->explosionPos = explosionPos;
	K = 1000000;
}

ExplosionForceGenerator::~ExplosionForceGenerator()
{

}

void ExplosionForceGenerator::updateForce(Particle* p, double t)
{

	if (p != nullptr && ((p)->getPos()).magnitude() <= R) {
		elapsedTime += t;
		double r = (pow(p->getPos().x - explosionPos.x, 2) + pow(p->getPos().y - explosionPos.y, 2)
			+ pow(p->getPos().z - explosionPos.z, 2));

		p->addForce(K/r * Vector3(p->getPos().x - explosionPos.x, p->getPos().y - explosionPos.y,
			p->getPos().z - explosionPos.z) * exp(-elapsedTime/tau));

		R += expandForce(t);

		//std::cout << K / r * (p->getPos().y - explosionPos.y) * exp(-elapsedTime / tau) << " ";
		
	}
}

double ExplosionForceGenerator::expandForce(double t) {
	return expanseVel.magnitude() * elapsedTime;
}

void ExplosionForceGenerator::enableExplosion()
{
	elapsedTime = 0;
}
