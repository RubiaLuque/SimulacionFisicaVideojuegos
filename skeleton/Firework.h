#pragma once
#include <list>
#include "core.hpp"
#include "Particle.h"
#include "Data.h"
#include "GravityForceGenerator.h"
#include <random>

using namespace std;
//class UniformParticleGenerator<Particle*>;
//class GaussianParticleGenerator<Particle*>;

class Firework
{
private:
	GravityForceGenerator* gr = new GravityForceGenerator();

	//almacena las particulas generadas
	vector<Particle*> particles;
	Particle* initP;

	std::mt19937 gen;
	std::uniform_real_distribution<double> dis{0, 1};

	std::mt19937 gen2;
	std::uniform_real_distribution<double> velD{-1, 3};
	std::uniform_int_distribution<int> numParticulas{15, 20};

	//posicion y velocidad base de la particula inicial
	Vector3 iniPos = { 0,0,0 };
	Vector3 iniVel = { 0.5, 13, 0.5};
	double elapsedTime = 0;
	double _life_time = 1.5;
	bool colors;
public:
	Firework();
	Firework(Vector3 pos, Vector4 color);
	virtual ~Firework();

	int update(double t);
	void shootParticle();
	vector<Particle*> explode(Particle* p);
	vector<Particle*> explodeWithColor(Particle* p, Vector4 color);
	inline void setAlive(Particle* p, bool alive) noexcept { p->alive = alive; };
};

