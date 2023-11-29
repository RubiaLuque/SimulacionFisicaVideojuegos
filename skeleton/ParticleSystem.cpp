#include "ParticleSystem.h"
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include "WindForceGenerator.h"
#include "VortexForceGenerator.h"
#include "AnchoredSpringForceGen.h"
#include "BuoyancyForceGenerator.h"
//#include "ExplosionForceGenerator.h"
#include <cmath>
#include <list>

ParticleSystem::ParticleSystem(Data::GENERATORS g)
{
	particles = std::list<Particle*>{};
	gens = std::vector<ParticleGenerator*>{};
	elapsedTime = 0;
	this->g = g;

	//FUENTE
	UniformParticleGenerator* fuente = new UniformParticleGenerator({ 0,-10,0 }, { 0, 5,0 }, {1, 10, 1}, { 10,10,10 }, Data::FUENTE);
	gens.push_back(fuente);

	//LLUVIA
	UniformParticleGenerator* lluvia = new UniformParticleGenerator({ 0, 50,0 }, { 0, 0, 0 }, { 30, 3, 30 }, { 1, 5, 1 }, Data::LLUVIA);
	gens.push_back(lluvia);

	//NIEVE
	GaussianParticleGenerator* nieve = new GaussianParticleGenerator({ 0,20,0 }, { 0,1,0 }, { 50, 5,  50}, { 5, 5, 5 }, Data::NIEVE);
	gens.push_back(nieve);

	//NIEBLA
	GaussianParticleGenerator* niebla = new GaussianParticleGenerator({ 0,10,0 }, { 1,1,1 }, { 50, 50, 50 }, { 1, 5, 1 }, Data::NIEBLA);
	gens.push_back(niebla);
}

void ParticleSystem::addForce(Data::FORCES f) {
	this->f = f;

	WindForceGenerator* w = new WindForceGenerator({0, 20, 0});
	forces.push_back(w);

	VortexForceGenerator* v = new VortexForceGenerator({0, 0, 0}, {0,0,0});
	forces.push_back(v);

	e = new ExplosionForceGenerator({ 0,20,0 });
	forces.push_back(e);

}

ParticleSystem::~ParticleSystem()
{
	//destruir uno a uno
	for (auto it = gens.begin(); it != gens.end(); ++it) {
		if (*it != nullptr) {
			delete* it;
			*it = nullptr;
		}
	}
	gens.clear();

	for (auto it = particles.begin(); it != particles.end(); ++it) {
		if (*it != nullptr) {
			delete* it;
			*it = nullptr;
		}
	}
	particles.clear();
}

void ParticleSystem::update(double t) {
	if (g != Data::NONE)
	{
		auto aux = gens.at(g)->generateParticles();


		for (auto it = aux.begin(); it != aux.end(); ++it) {
			particles.push_back(*it);
			fr->addRegistry(gr, *it);
		}

	}

	for (auto it = particles.begin(); it != particles.end(); ++it) {
		//A todas las particulas les afecta la gravedad
		if (f == Data::WIND) {
			fr->addRegistry(forces.at(f - 1), *it);
		}
		else if (f == Data::VORTEX) {
			fr->addRegistry(forces.at(f - 1), *it);
		}
		else if (f == Data::EXPLOSION) {
			fr->addRegistry(forces.at(f - 1), *it);
		}
	}

	//eliminar aquellas que lleven mas tiempo del necesario en pantalla
	for (auto it = particles.begin(); it != particles.end(); ++it) {
		(*it)->limit_time += t;
		if ((*it)->limit_time > Data::LIMIT_ON_SCREEN) {
			//se marca como no vivo
			setAlive((*it), false);

			particles.erase(remove_if(particles.begin(), particles.end(),
				[&](Particle* p) {
					if (p->alive) return false;
					else { //si no esta vivo, se elimina
						fr->deleteParticleRegistry(p);
						delete p;
						return true;
					}
				}), particles.end()
					);
		}
	}

	fr->updateForces(t);

	//se hace update de todas las demas
	for (auto it = particles.begin(); it != particles.end(); ++it) {
		(*it)->update(t);
	}


}

void ParticleSystem::generateSpring()
{
	//Muelle entre 2 particulas
	Particle* p1 = new Particle({ -20, 20, 0 }, { 0,0,0 }, 0.85, 1, 0.98, Data::IDLE);
	Particle* p2 = new Particle({ 20, 20, 0 }, { 0,0,0 }, 2.0, 2.0, 0.98, Data::IDLE);
	
	SpringForceGenerator* f1 = new SpringForceGenerator(1, 10, p2);
	SpringForceGenerator* f2 = new SpringForceGenerator(1, 10, p1);

	fr->addRegistry(f1, p1);
	fr->addRegistry(f2, p2);

	forces.push_back(f1);
	forces.push_back(f2);
	particles.push_back(p1);
	particles.push_back(p2);

	//Muelle entre una particula con la pared
	Particle* p3 = new Particle({ 0, -20, 0 }, { 0,0,0 }, 1.0, 1.0, 0.988, Data::IDLE);
	AnchoredSpringForceGen* f3 = new AnchoredSpringForceGen(1, 10, { 0, 10, 0 });
	fr->addRegistry(f3, p3);
	forces.push_back(f3);
	particles.push_back(p3);

	fr->addRegistry(gr, p3);
}

void ParticleSystem::generateSlinky() {
	Particle* p1 = new Particle({ 0, 10,0 }, { 0,0,0 }, { 0,0,0 }, { 1.0, 0.0,0.0,1.0 }, 1.0, 2.0, 0.988, Data::IDLE); //rojo
	Particle* p2 = new Particle({ 0, 0,0 }, { 0,0,0 }, { 0,0,0 }, { 1.0, 0.5, 0.0, 1.0 }, 1.0, 2.0, 0.988, Data::IDLE); //naranja
	Particle* p3 = new Particle({ 0, -10,0 }, { 0,0,0 }, { 0,0,0 }, { 1.0, 1.0, 0.0, 1.0 }, 1.0, 2.0, 0.988, Data::IDLE); //amarillo
	Particle* p4 = new Particle({ 0, -20,0 }, { 0,0,0 }, { 0,0,0 }, { 0.0, 1.0, 0.0, 1.0 }, 1.0, 2.0, 0.988, Data::IDLE); //verde
	Particle* p5 = new Particle({ 0, -30,0 }, { 0,0,0 }, { 0,0,0 }, { 0.0, 0.0, 1.0, 1.0 }, 1.0, 2.0, 0.988, Data::IDLE); //azul

	//Fuerzas entre p1 y p2
	SpringForceGenerator* f1 = new SpringForceGenerator(10, 1, p2);
	SpringForceGenerator* f2 = new SpringForceGenerator(10, 1, p1);

	fr->addRegistry(f1, p1); 
	fr->addRegistry(f2, p2);

	//Fuerzas entre p2 y p3
	SpringForceGenerator* f3 = new SpringForceGenerator(10, 1, p3);
	SpringForceGenerator* f4 = new SpringForceGenerator(10, 1, p2);
	fr->addRegistry(f3, p2);
	fr->addRegistry(f4, p3);

	//Fuerzas entre p3 y p4
	SpringForceGenerator* f5 = new SpringForceGenerator(10, 1, p4);
	SpringForceGenerator* f6 = new SpringForceGenerator(10, 1, p3);
	fr->addRegistry(f5, p3);
	fr->addRegistry(f6, p4);

	//Fuerzas entre p4 y p5
	SpringForceGenerator* f7 = new SpringForceGenerator(10, 1, p5);
	SpringForceGenerator* f8 = new SpringForceGenerator(10, 1, p4);
	fr->addRegistry(f7, p4);
	fr->addRegistry(f8, p5);

	forces.push_back(f1);
	forces.push_back(f2);
	forces.push_back(f3);
	forces.push_back(f4);
	forces.push_back(f5);
	forces.push_back(f6);
	forces.push_back(f7);
	forces.push_back(f8);

	particles.push_back(p1);
	particles.push_back(p2);
	particles.push_back(p3);
	particles.push_back(p4);
	particles.push_back(p5);

	/*fr->addRegistry(gr, p2);
	fr->addRegistry(gr, p3);
	fr->addRegistry(gr, p4);
	fr->addRegistry(gr, p5);*/

}

void ParticleSystem::generateBuoyancyWater() {
	float height = 10.0;
	BuoyancyForceGenerator* b = new BuoyancyForceGenerator(height, 1, 1000);
	Particle* p = new Particle({ 0, 30, 0 }, { 0,0,0 }, 50, height/2, 0.98, Data::IDLE);
	fr->addRegistry(b, p);
	fr->addRegistry(gr, p);

	forces.push_back(b);
	particles.push_back(p);
}

void ParticleSystem::generateBuoyancyMercury()
{
	float height = 10.0;
	BuoyancyForceGenerator* b = new BuoyancyForceGenerator(height, 1, 13600);
	Particle* p = new Particle({ 0, 30, 0 }, { 0,0,0 }, { 0,0,0 }, { 0.8, 0.8, 0.8, 1.0 }, 1000, height / 2, 0.98, Data::IDLE);
	fr->addRegistry(b, p);
	fr->addRegistry(gr, p);

	forces.push_back(b);
	particles.push_back(p);
}

void ParticleSystem::setK(int op)
{
	/*for (auto it = forces.begin(); it != forces.end(); ++it) {
		if ((*it) == dynamic_cast<SpringForceGenerator*>(*it)) {
			if (op == 0) (*it)->increaseK();
			else (*it)->decreaseK();
		}
	}*/
}
