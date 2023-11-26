#pragma once
#include "ForceGenerator.h"
#include <map>

typedef std::pair<ForceGenerator*, Particle*> FRPair;

class ForceRegistry : public std::multimap<ForceGenerator*, Particle*>
{
private:

public:
	void updateForces(double t);
	void addRegistry(ForceGenerator* f, Particle* p);
	void deleteParticleRegistry(Particle* p);

};

