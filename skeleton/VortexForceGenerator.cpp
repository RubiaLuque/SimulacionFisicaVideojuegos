#include "VortexForceGenerator.h"

VortexForceGenerator::VortexForceGenerator(Vector3 windVel, Vector3 vortexPos) : WindForceGenerator(windVel)
{
	this->vortexPos = vortexPos;
	K = 10;
}

void VortexForceGenerator::applyForce(Particle* p)
{
	if (p != nullptr) {
		p->setVel(K * Vector3(-(p->getPos().z - this->vortexPos.z), 
			50-(p->getPos().y - this->vortexPos.y), p->getPos().x - this->vortexPos.x ));
	}
}

void VortexForceGenerator::removeForce(Particle* p)
{

}
