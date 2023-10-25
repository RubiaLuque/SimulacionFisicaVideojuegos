#pragma once

#include <vector>
#include "core.hpp"
#include "Data.h"
#include "ParticleGenerator.h"
#include "Particle.h"

using namespace std;
//Esta clase almacena las particulas creadas y las destruye a su debido tiempo
class ParticleSystem
{
private:
	//lista de particulas
	vector<ParticleGenerator*> gens;
	Data::GENERATORS g;

	//vector<Firework*> fireworks_pool;
	
	list<Particle*> particles;
	double elapsedTime;

public:
	ParticleSystem(Data::GENERATORS gen);
	virtual ~ParticleSystem();
	void update(double t);
	void shootFirework(int type);
	void onParticleDeath(Particle* p);
	void generateFireworkSystem();

	//cambia la propiedad alive de las particulas 
	inline void setAlive(Particle* p, bool alive) noexcept { p->alive = alive; }
};

