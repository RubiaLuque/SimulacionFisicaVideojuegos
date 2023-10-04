#pragma once
#include "Render/Camera.h"
#include "Particle.h"
#include <vector>

using namespace std;

class SceneManager
{
private:
	//vector de proyectiles
	vector<Particle*> projectiles;
	//referencia a la camara
	Camera* cam;
	//tiempo limite en pantalla (comun a todas las particulas)
	double LIMIT_ON_SCREEN = 20.0;

public:
	SceneManager() noexcept;

	~SceneManager();

	//añade proyectiles al vector
	void addProjectile(PROJECTILE_TYPE type);

	void update(double t);

	//cambia la propiedad alive de las particulas 
	inline void setAlive(Particle* p, bool alive) { p->alive = alive; }
};

