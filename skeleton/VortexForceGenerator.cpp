#include "VortexForceGenerator.h"

VortexForceGenerator::VortexForceGenerator(Vector3 windVel, Vector2 vortexPos) : WindForceGenerator(windVel)
{
	this->vortexPos = vortexPos;
	//K = 
}

void VortexForceGenerator::applyForce(Particle* p)
{

}

void VortexForceGenerator::removeForce(Particle* p)
{

}
