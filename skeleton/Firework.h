#pragma once
#include <list>
#include "core.hpp"
#include "Particle.h"
using namespace std;

class Firework : public Particle
{
private:
	//almacena las particulas generadas
	list<Particle*> gens;

public:
	int update(double t);
	virtual Particle* clone() const;
	list<Particle*> explode();
};

