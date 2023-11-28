#include "VortexForceGenerator.h"

VortexForceGenerator::VortexForceGenerator(Vector3 windVel, Vector3 vortexPos) : WindForceGenerator(windVel)
{
	this->vortexPos = vortexPos;
	K = 1;
}

void VortexForceGenerator::updateForce(Particle* p, double t)
{
	if (p != nullptr && ((p)->getPos()).magnitude() <= Data::vortexSphereRadius) {

		this->windVel = K * Vector3(-(p->getPos().z - this->vortexPos.z),
			100 - (p->getPos().y - this->vortexPos.y), p->getPos().x - this->vortexPos.x);
		
		p->addForce(k1 * (windVel - p->getVel()) +
			k2 * (windVel - p->getVel()).magnitude() * (windVel - p->getVel()));

	}
}

void VortexForceGenerator::removeForce(Particle* p)
{

}
