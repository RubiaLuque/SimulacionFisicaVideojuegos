#include "SceneManager.h"
#include "GravityForceGenerator.h"

SceneManager::SceneManager(PxPhysics* gPhysics, PxScene* gScene) {
	cam = GetCamera();
	particleSys = false;
	fire = false;
	this->gPhysics = gPhysics;
	this->gScene = gScene;
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
		sys.push_back(new ParticleSystem(FUENTE, gPhysics, gScene));
	}
	else if (gen == LLUVIA) {
		sys.push_back(new ParticleSystem(LLUVIA, gPhysics, gScene));
	}
	else if (gen == NIEVE) {
		sys.push_back(new ParticleSystem(NIEVE, gPhysics, gScene));
	}
	else if(gen == NIEBLA){ //NIEBLA
		sys.push_back(new ParticleSystem(NIEBLA, gPhysics, gScene));
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
	for (auto it = particles.begin(); it != particles.end(); it++) {
		(*it)->limit_time += t;
		if ((*it)->limit_time > Data::LIMIT_ON_SCREEN) {
			//se marca como no vivo
			setAlive(*it, false);
		}
	}

	particles.erase(remove_if(particles.begin(), particles.end(),
		[](Particle* p) noexcept {
			if (p->alive) return false;
			else { //si no esta vivo, se elimina
				delete p;
				return true;
			}
		}), particles.end());

	//fr->updateForces(t);

	//se hace update de todas las demas
	for (auto* particle : particles) {
		particle->update(t);
	}

	//Se hace update de los sistemas de particulas
	for (auto* system : sys) {
		system->update(t);
	}

	if (fire) firework->update(t);
}

void SceneManager::generateSpring()
{
	//Se borran los otros sistemas a a�adir un sistema con muelles, para que sea mas facil visualizarlo
	//Comentar la sigiente linea para combinar varios sistemas con muelles
	for (auto* system : sys) {
		delete system;
	}
	sys.clear();
	ParticleSystem* s = new ParticleSystem(NONE, gPhysics, gScene);
	sys.push_back(s);
	s->generateSpring();
}

void SceneManager::generateSlinky()
{
	for (auto* system : sys) {
		delete system;
	}
	sys.clear();
	ParticleSystem* s = new ParticleSystem(NONE, gPhysics, gScene);
	sys.push_back(s);
	s->generateSlinky();
}

void SceneManager::setK(int op)
{
	for (auto* system : sys) {
		system->setK(op);
	}
}

void SceneManager::generateBuoyancyWater()
{
	for (auto* system : sys) {
		delete system;
	}
	sys.clear();
	ParticleSystem* s = new ParticleSystem(NONE, gPhysics, gScene);
	sys.push_back(s);
	s->generateBuoyancyWater();
}

void SceneManager::generateBuoyancyMercury()
{
	for (auto* system : sys) {
		delete system;
	}
	sys.clear();
	ParticleSystem* s = new ParticleSystem(NONE, gPhysics, gScene);
	sys.push_back(s);
	s->generateBuoyancyMercury();
}

void SceneManager::addFirework()
{
	firework = new Firework();
	fire = true;
	firework->shootParticle();
}
