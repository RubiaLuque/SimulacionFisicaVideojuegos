#include "ParticleSystem.h"
#include "SceneManager.h"

ParticleSystem::ParticleSystem()
{
	particles = std::list<Particle*>{};
	elapsedTime = 0;
}

void ParticleSystem::update(double t) {
	elapsedTime += t;
	if (elapsedTime >= NEW_PARTICLE_TIME) {
		particles.push_back(new Particle({ 0,0,0 }, { 20,30,0 }, { 0, -9.8, 0 }, 1.0, 0.988, GENERATION));
		elapsedTime = 0;
	}

	//eliminar aquellas que lleven mas tiempo del necesario en pantalla
	for (auto it = particles.begin(); it != particles.end(); ++it) {
		(*it)->limit_time += t;
		if ((*it)->limit_time > LIMIT_ON_SCREEN) {
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

	//se hace update de todas las demas
	for (auto it = particles.begin(); it != particles.end(); ++it) {
		(*it)->update(t);
	}

	
}

void ParticleSystem::shootFirework(int type)
{
}

void ParticleSystem::onParticleDeath(Particle* p)
{
}

void ParticleSystem::generateFireworkSystem()
{
}
