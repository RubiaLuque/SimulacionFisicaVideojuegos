#include "SceneManager.h"
#include "GravityForceGenerator.h"

SceneManager::SceneManager() {
	cam = GetCamera();
	particleSys = false;
	fire = false;
}

SceneManager::~SceneManager() {

	for (int i = 0; i < particles.size(); ++i) {
		if (particles.at(i) != nullptr) {
			delete particles.at(i);
			particles.at(i) = nullptr;

		}
	}
	particles.clear();

	for (int i = 0; i < sys.size(); ++i) {
		if (sys.at(i) != nullptr) {
			delete sys.at(i);
			sys.at(i) = nullptr;
		}
	}
	sys.clear();

}

void SceneManager::addParticleSystem(GENERATORS gen) {
	if (gen == FUENTE) {
		sys.push_back(new ParticleSystem(FUENTE));
	}
	else if (gen == LLUVIA) {
		sys.push_back(new ParticleSystem(LLUVIA));
	}
	else if (gen == NIEVE) {
		sys.push_back(new ParticleSystem(NIEVE));
	}
	else if(gen == NIEBLA){ //NIEBLA
		sys.push_back(new ParticleSystem(NIEBLA));
	}
}

void SceneManager::addForceToSystem(FORCES f) {
	Particle* explosion = nullptr;
	Particle* vortex = nullptr; 
	Particle* wind = nullptr;
	for (int i = 0; i < sys.size(); ++i) {
		if (sys.at(i) != nullptr) {
			sys.at(i)->addForce(f);
			
			if (f == Data::EXPLOSION) {
				explosion = new Particle({ 0,20,0 }, { 0,0,0 }, 0, { 0,0,0,0 }, Data::EXPLOSION_SPHERE_RADIUS, 0, NONE);
				sys.at(i)->getExplosion()->enableExplosion();
			}
			else if (f == Data::VORTEX) {
				vortex = new Particle({ 0,0,0 }, { 0,0,0 }, 0, { 0,0,0,0 }, Data::vortexSphereRadius, 0, NONE);
				
			}
			else if (f == Data::WIND) {
				wind = new Particle({ 0,0,0 }, { 0,0,0 }, 0, { 0,0,0,0 }, Data::windSphereRadius, 0, NONE);
			}


		}
	}
}

void SceneManager::addProjectile(PROJECTILE_TYPE type) {
	Vector3 vel = cam->getDir();
	const Vector3 pos = cam->getEye();

	GravityForceGenerator* g = new GravityForceGenerator();

	if (type == FIREBALL) {
		vel *= 10;
		//const Vector3 acc = { 0.0, -0.6, 0.0 }; //muy poca gravedad porque se quiere simular que flota un poco -> P1
		auto p = new Particle(pos, vel, 0.0001, 3.0, 0.888, FIREBALL);
		particles.push_back(p);
		fr->addRegistry(g, p);
	}
	else if (type == LIGHTGUN)
	{
		vel *= 25;
		//Vector3 acc = { 0.0, 0.0, 0.0 }; //no tiene efecto gravedad -> P1
		auto p = new Particle(pos, vel, 0.0, 1.0, 0.998, LIGHTGUN);
		particles.push_back(p);
		fr->addRegistry(g, p);
	}
	else if (type == GUN) {
		vel *= 20;
		//const Vector3 acc = { 0.0, -1.0, 0.0 }; //poco efecto de la gravedad -> P1
		auto p = new Particle(pos, vel, 0.1, 1.0, 0.998, GUN);
		particles.push_back(p);
		fr->addRegistry(g, p);
	}
	else //cannon
	{
		vel *= 18;
		//const Vector3 acc = { 0.0, -5.0, 0.0 }; //bastante efecto de gravedad -> P1
		auto p = new Particle(pos, vel, 3.0, 5.0, 0.998, CANNON);
		particles.push_back(p);
		fr->addRegistry(g, p);
	}

}


void SceneManager::update(double t) {

	//eliminar aquellas que lleven mas tiempo del necesario en pantalla
	for (int i = 0; i < particles.size(); ++i) {
		particles.at(i)->limit_time += t;
		if (particles.at(i)->limit_time > Data::LIMIT_ON_SCREEN) {
			//se marca como no vivo
			setAlive(particles.at(i), false);

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
	for (int i = 0; i < particles.size(); ++i) {
		particles.at(i)->update(t);
	}

	//Se hace update de los sistemas de particulas
	for (int i = 0; i < sys.size(); ++i) {
		sys.at(i)->update(t);
	}

	if (fire) firework->update(t);
}

void SceneManager::generateSpring()
{
	ParticleSystem* s = new ParticleSystem(NONE);
	sys.push_back(s);
	s->generateSpring();
}

void SceneManager::generateSlinky()
{
	ParticleSystem* s = new ParticleSystem(NONE);
	sys.push_back(s);
	s->generateSlinky();
}

void SceneManager::addFirework()
{
	firework = new Firework();
	fire = true;
	firework->shootParticle();
}


