#pragma once

#include <vector>
#include "core.hpp"
#include "ParticleGenerator.h"
#include "Particle.h"

using namespace std;
const double NEW_PARTICLE_TIME = 0.1;
//Esta clase almacena las particulas creadas y las destruye a su debido tiempo
class ParticleSystem
{
private:
	vector<Firework*> fireworks_pool;
	ParticleGenerator* firework_gen;
	list<Particle*> particles;
	double elapsedTime;

public:
	ParticleSystem();
	~ParticleSystem();
	void update(double t);
	void shootFirework(int type);
	void onParticleDeath(Particle* p);
	void generateFireworkSystem();

	//cambia la propiedad alive de las particulas 
	inline void setAlive(Particle* p, bool alive) { p->alive = alive; }
};

