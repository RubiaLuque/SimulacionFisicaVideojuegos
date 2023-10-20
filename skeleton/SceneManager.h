#pragma once
#include "Render/Camera.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include <vector>

using namespace std;

static const double LIMIT_ON_SCREEN = 20.0;

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
	SceneManager() noexcept;

	~SceneManager();

	//añade proyectiles al vector
	void addProjectile(PROJECTILE_TYPE type);

	void update(double t);

	//cambia la propiedad alive de las particulas 
	inline void setAlive(Particle* p, bool alive) { p->alive = alive; }
};

