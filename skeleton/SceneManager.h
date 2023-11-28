#pragma once
#include "Render/Camera.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include "ForceRegistry.h"
#include <vector>
#include "Data.h"
#include "Firework.h"

using namespace std;
using namespace Data;

class SceneManager
{
private:
	//vector de proyectiles
	vector<Particle*> particles;
	//referencia a la camara
	Camera* cam;
	vector<ParticleSystem*> sys;
	vector<ParticleSystem*> forces;

	Firework* firework;
	ForceRegistry* fr = new ForceRegistry();
	bool particleSys;
	bool fire;

public:
	SceneManager();

	virtual ~SceneManager();

	//añade proyectiles al vector
	void addProjectile(PROJECTILE_TYPE type);
	void addParticleSystem(GENERATORS gen);
	void addForceToSystem(FORCES f);
	void addFirework();
	void update(double t);

	//cambia la propiedad alive de las particulas 
	inline void setAlive(Particle* p, bool alive) { p->alive = alive; }
};

