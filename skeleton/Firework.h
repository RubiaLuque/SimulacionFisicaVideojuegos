#pragma once
#include <list>
#include "core.hpp"
#include "Particle.h"
#include "Data.h"
#include <random>

using namespace std;
class UniformParticleGenerator;
class GaussianParticleGenerator;

class Firework
{
private:
	//almacena las particulas generadas
	vector<Particle*> particles;
	Particle* initP;

	std::mt19937 gen;
	std::uniform_real_distribution<double> dis{0, 1};

	std::uniform_real_distribution<double> posD{10, 20};
	std::uniform_real_distribution<double> velD{3, 6};
	std::uniform_int_distribution<int> numParticulas{3, 10};

	//posicion y velocidad base de la particula inicial
	Vector3 iniPos = { 0,0,0 };
	Vector3 iniVel = { 1, 5, 1 };
	double elapsedTime;

public:
	Firework();
	virtual ~Firework();
	int update(double t);
	void shootParticle();
	list<Particle*> explode(Particle* p);
	inline void setAlive(Particle* p, bool alive) noexcept { p->alive = alive; };
};

