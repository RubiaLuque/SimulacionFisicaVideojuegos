#pragma once
#include <list>
#include "core.hpp"
#include "Particle.h"

using namespace std;

class Firework
{
private:
	//almacena las particulas generadas
	list<Particle*> gens;

public:
	Firework();
	~Firework();
	int update(double t);
	void shootParticle();
	list<Particle*> explode(Particle* p);
};

