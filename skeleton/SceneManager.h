#pragma once
#include "Render/Camera.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include <vector>
#include "Data.h"

using namespace std;
using namespace Data;

static const double LIMIT_ON_SCREEN = 4.0;

class SceneManager
{
private:
	//vector de proyectiles
	vector<Particle*> particles;
	//referencia a la camara
	Camera* cam;
	ParticleSystem* sys;
	bool particleSys;

public:
	SceneManager();

	~SceneManager();

	//añade proyectiles al vector
	void addProjectile(PROJECTILE_TYPE type);

	void update(double t);

	//cambia la propiedad alive de las particulas 
	inline void setAlive(Particle* p, bool alive) { p->alive = alive; }
};

