#include "ParticleSystem.h"
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include "WindForceGenerator.h"
#include "VortexForceGenerator.h"
//#include "ExplosionForceGenerator.h"
#include <cmath>

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

	//IDLE
	UniformParticleGenerator* idle = new UniformParticleGenerator({ 0,50,0 }, { 0,0,0 }, { 10, 0, 10 }, { 0,0,0 }, Data::IDLE);
	gens.push_back(idle);
}

void ParticleSystem::addForce(Data::FORCES f) {
	this->f = f;

	WindForceGenerator* w = new WindForceGenerator({0, 20, 0});
	forces.push_back(w);

	VortexForceGenerator* v = new VortexForceGenerator({0, 0, 0}, {0,0,0});
	forces.push_back(v);

	e = new ExplosionForceGenerator({ 0,20,0 });
	forces.push_back(e);

	fr->addRegistry(forces.at(f-1), nullptr);
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

	auto aux = gens.at(g)->generateParticles();


	for (auto it = aux.begin(); it != aux.end(); ++it) {
		particles.push_back(*it);
		//A todas las particulas les afecta la gravedad
		fr->addRegistry(gr, *it);
		for (int i = 0; i < forces.size(); ++i) {
			fr->addRegistry(forces[i], *it);
		}
	}




	//eliminar aquellas que lleven mas tiempo del necesario en pantalla
	for (auto it = particles.begin(); it != particles.end(); ++it) {
		(*it)->limit_time += t;
		if ((*it)->limit_time > Data::LIMIT_ON_SCREEN) {
			//se marca como no vivo
			setAlive((*it), false);

			particles.erase(remove_if(particles.begin(), particles.end(),
				[](Particle* p) noexcept {
					if (p->alive) return false;
					else { //si no esta vivo, se elimina
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
