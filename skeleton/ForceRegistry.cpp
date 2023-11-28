#include "ForceRegistry.h"

ForceRegistry::~ForceRegistry()
{
	this->clear();
}

void ForceRegistry::updateForces(double t)
{
	for (auto it = begin(); it != end(); ++it) {
		if(it->second!= nullptr)
			it->first->updateForce(it->second, t);
	}
}

void ForceRegistry::addRegistry(ForceGenerator* f, Particle* p)
{
	this->insert({ f, p });
	//auto itForce = find(f);
	////La fuerza no estaba registrada
	//if (itForce == end()) {
	//}
	//else {
	//	itForce->second = p;
	//}
}

void ForceRegistry::deleteParticleRegistry(Particle* p)
{
	
}
