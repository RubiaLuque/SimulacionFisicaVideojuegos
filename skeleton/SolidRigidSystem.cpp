#include "SolidRigidSystem.h"
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include "WindForceGenerator.h"
#include "VortexForceGenerator.h"
#include "AnchoredSpringForceGen.h"
#include "BuoyancyForceGenerator.h"
#include "BungeeForceGenerator.h"
#include "UniformSR.h"
#include "GaussianSR.h"
#include <cmath>
#include <list>

SolidRigidSystem::SolidRigidSystem(Data::GENERATORS g, PxPhysics* gPhysics, PxScene* gScene)
{
	this->g = g;
	this->gScene = gScene;
	this->gPhysics = gPhysics;

	gens = std::vector<ParticleGenerator<SolidRigid>*>{};
	elapsedTime = 0;
	//FUENTE
	UniformParticleGenerator<SolidRigid>* fuente = new UniformSR({ 0,-10,0 }, { 0, 5,0 }, { 1, 10, 1 }, { 10,10,10 }, Data::FUENTE, gPhysics, gScene);
	gens.push_back(fuente);

	//LLUVIA
	UniformParticleGenerator<SolidRigid>* lluvia = new UniformSR
		({ 0, 50,0 }, { 0, 0, 0 }, { 30, 3, 30 }, { 1, 5, 1 }, Data::LLUVIA, gPhysics, gScene);
	gens.push_back(lluvia);

	//NIEVE
	GaussianParticleGenerator<SolidRigid>* nieve = new GaussianSR
		({ 0,20,0 }, { 0,1,0 }, { 50, 5,  50 }, { 5, 5, 5 }, Data::NIEVE, gPhysics, gScene);
	gens.push_back(nieve);

	//NIEBLA
	GaussianParticleGenerator<SolidRigid>* niebla = new GaussianSR
		({ 0,10,0 }, { 1,1,1 }, { 50, 50, 50 }, { 1, 5, 1 }, Data::NIEBLA, gPhysics, gScene);
	gens.push_back(niebla);
}

SolidRigidSystem::~SolidRigidSystem()
{
	//destruir uno a uno
	for (auto it = gens.begin(); it != gens.end(); ++it) {
		if (*it != nullptr) {
			delete* it;
			*it = nullptr;
		}
	}
	gens.clear();

	for (auto it = solids.begin(); it != solids.end(); ++it) {
		if (*it != nullptr) {
			delete* it;
			*it = nullptr;
		}
	}
	solids.clear();

	for (auto it = forces.begin(); it != forces.end(); ++it) {
		if (*it != nullptr) {
			delete* it;
			*it = nullptr;
		}
	}
	forces.clear();

	for (auto it = forcesT.begin(); it != forcesT.end(); ++it) {
		if (*it != nullptr) {
			delete* it;
			*it = nullptr;
		}
	}
	forcesT.clear();

	delete fr;
	delete frT;
}

void SolidRigidSystem::addForce(Data::FORCES f)
{
	this->f = f;

	WindForceGenerator<SolidRigid>* w = new WindForceGenerator<SolidRigid>({ 0, 20, 0 });
	forces.push_back(w);

	VortexForceGenerator<SolidRigid>* v = new VortexForceGenerator<SolidRigid>({ 0, 0, 0 }, { 0,0,0 });
	forces.push_back(v);

	e = new ExplosionForceGenerator<SolidRigid>({ 0,20,0 });
	forces.push_back(e);
}

void SolidRigidSystem::update(double t)
{
	if (g != Data::NONE)
	{
		auto aux = gens.at(g)->generateParticles();


		for (auto it = aux.begin(); it != aux.end(); ++it) {
			solids.push_back(*it);
		}

	}
	for (auto it = solids.begin(); it != solids.end(); ++it) {
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
	for (auto it = solids.begin(); it != solids.end(); ++it) {
		(*it)->limit_time += t;
		if ((*it)->limit_time > Data::LIMIT_ON_SCREEN) {
			//se marca como no vivo
			setAlive((*it), false);
		}
	}

	solids.erase(remove_if(solids.begin(), solids.end(),
		[&](SolidRigid* p) {
			if (p->alive) return false;
			else { //si no esta vivo, se elimina
				fr->deleteParticleRegistry(p);
				delete p;
				return true;
			}
		}), solids.end());

	fr->updateForces(t);
	frT->updateForces(t);
}

void SolidRigidSystem::generateSpring()
{
	//Muelle entre 2 particulas
	SolidRigid* p1 = new SolidRigid({ -20, 20, 0 }, { 0,0,0 }, { 0,0,0 }, { 0.3, 0.8, 0.0, 1.0 }, 10, 1, Data::DYNAMIC, gPhysics, gScene);
	SolidRigid* p2 = new SolidRigid({ 20, 20, 0 }, { 0,0,0 }, { 0,0,0 }, { 0.3, 0.8, 0.0, 1.0 }, 20, 2.0, Data::DYNAMIC, gPhysics, gScene);

	SpringForceGenerator<SolidRigid>* f1 = new SpringForceGenerator<SolidRigid>(500, 10, p2);
	SpringForceGenerator<SolidRigid>* f2 = new SpringForceGenerator<SolidRigid>(500, 10, p1);

	fr->addRegistry(f1, p1);
	fr->addRegistry(f2, p2);

	forces.push_back(f1);
	forces.push_back(f2);
	solids.push_back(p1);
	solids.push_back(p2);

	//Muelle entre una particula con la pared
	SolidRigid* p3 = new SolidRigid({ 5, -20, 0 }, { 0,0,0 }, { 0,0,0 }, {1,1,1,1}, 1.0, 1.0, Data::DYNAMIC, gPhysics, gScene);
	AnchoredSpringForceGen<SolidRigid>* f3 = new AnchoredSpringForceGen<SolidRigid>(5, 10, { 5, 10, 0 });
	fr->addRegistry(f3, p3);
	forces.push_back(f3);
	solids.push_back(p3);

	SolidRigid* p4 = new SolidRigid({ -10, 30, 0 }, { 0,0,0 }, { 0,0,0 }, { 1.0, 0.5, 0.0, 1.0 }, 30, 2,Data::DYNAMIC, gPhysics, gScene);
	SolidRigid* p5 = new SolidRigid({ 10, 30, 0 }, { 0,0,0 }, { 0,0,0 }, { 1.0, 0.5, 0.0, 1.0 }, 30, 2, Data::DYNAMIC, gPhysics, gScene);
	SpringForceGenerator<SolidRigid>* f4 = new SpringForceGenerator<SolidRigid>(500, 10, p5);
	SpringForceGenerator<SolidRigid>* f5 = new SpringForceGenerator<SolidRigid>(500, 10, p4);

	fr->addRegistry(f4, p4);
	fr->addRegistry(f5, p5);

	forces.push_back(f4);
	forces.push_back(f5);
	solids.push_back(p4);
	solids.push_back(p5);
}

void SolidRigidSystem::generateSpringTargets(Target* t1, Target* t2)
{
	SpringForceGenerator<Target>* f1 = new SpringForceGenerator<Target>(100, 200, t2);
	SpringForceGenerator<Target>* f2 = new SpringForceGenerator<Target>(100, 200, t1);

	frT->addRegistry(f1, t1);
	frT->addRegistry(f2, t2);

	forcesT.push_back(f1);
	forcesT.push_back(f2);
}

void SolidRigidSystem::generateSlinky()
{
	SolidRigid* p1 = new SolidRigid({ 0, 50,0 }, { 0,0,0 }, { 0,0,0 }, { 1.0, 0.0,0.0,1.0 }, 5, 2.0, Data::DYNAMIC, gPhysics, gScene); //rojo
	SolidRigid* p2 = new SolidRigid({ 0, 35,0 }, { 0,0,0 }, { 0,0,0 }, { 1.0, 0.5, 0.0, 1.0 }, 5, 2.0, Data::DYNAMIC, gPhysics, gScene); //naranja
	SolidRigid* p3 = new SolidRigid({ 0, 15,0 }, { 0,0,0 }, { 0,0,0 }, { 1.0, 1.0, 0.0, 1.0 }, 5, 2.0, Data::DYNAMIC, gPhysics, gScene); //amarillo
	SolidRigid* p4 = new SolidRigid({ 0, 0,0 }, { 0,0,0 }, { 0,0,0 }, { 0.0, 1.0, 0.0, 1.0 }, 5.0, 2.0, Data::DYNAMIC, gPhysics, gScene); //verde
	SolidRigid* p5 = new SolidRigid({ 0, -15,0 }, { 0,0,0 }, { 0,0,0 }, { 0.0, 0.0, 1.0, 1.0 }, 5.0, 2.0, Data::DYNAMIC, gPhysics, gScene); //azul

	//Fuerzas entre p1 y p2
	SpringForceGenerator<SolidRigid>* f1 = new SpringForceGenerator<SolidRigid>(600, 10, p2);
	SpringForceGenerator<SolidRigid>* f2 = new SpringForceGenerator<SolidRigid>(600, 10, p1);

	fr->addRegistry(f1, p1);
	fr->addRegistry(f2, p2);

	//Fuerzas entre p2 y p3
	SpringForceGenerator<SolidRigid>* f3 = new SpringForceGenerator<SolidRigid>(400, 10, p3);
	SpringForceGenerator<SolidRigid>* f4 = new SpringForceGenerator<SolidRigid>(400, 10, p2);
	fr->addRegistry(f3, p2);
	fr->addRegistry(f4, p3);

	//Fuerzas entre p3 y p4
	SpringForceGenerator<SolidRigid>* f5 = new SpringForceGenerator<SolidRigid>(200, 10, p4);
	SpringForceGenerator<SolidRigid>* f6 = new SpringForceGenerator<SolidRigid>(200, 10, p3);
	fr->addRegistry(f5, p3);
	fr->addRegistry(f6, p4);

	//Fuerzas entre p4 y p5
	SpringForceGenerator<SolidRigid>* f7 = new SpringForceGenerator<SolidRigid>(100, 10, p5);
	SpringForceGenerator<SolidRigid>* f8 = new SpringForceGenerator<SolidRigid>(100, 10, p4);
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

	solids.push_back(p1);
	solids.push_back(p2);
	solids.push_back(p3);
	solids.push_back(p4);
	solids.push_back(p5);
}

void SolidRigidSystem::generateBuoyancyWater()
{
	float height = 10.0f;
	BuoyancyForceGenerator<SolidRigid>* b = new BuoyancyForceGenerator<SolidRigid>(height, 1, 1000);
	SolidRigid* p = new SolidRigid({ 0, 30, 0 }, { 0,0,0 }, { 0,0,0 }, {0.5, 0.3, 0.2, 1}, 50, height / 2, Data::DYNAMIC, gPhysics, gScene);
	fr->addRegistry(b, p);

	forces.push_back(b);
	solids.push_back(p);
}

void SolidRigidSystem::generateBuoyancyMercury()
{
	float height = 10.0f;
	BuoyancyForceGenerator<SolidRigid>* b = new BuoyancyForceGenerator<SolidRigid>(height, 0.8, 13600);
	SolidRigid* p = new SolidRigid({ 0, 30, 0 }, { 0,0,0 }, { 0,0,0 }, { 0.8, 0.8, 0.8, 1.0 }, 2000, height / 2, Data::DYNAMIC, gPhysics, gScene);
	fr->addRegistry(b, p);

	forces.push_back(b);
	solids.push_back(p);
}

void SolidRigidSystem::setK(int op)
{
	for (auto* force : forces) {
		if (SpringForceGenerator<SolidRigid>* spring = dynamic_cast<SpringForceGenerator<SolidRigid>*>(force)) {
			if (op == 0) spring->increaseK();
			else spring->decreaseK();
		}
	}
}
