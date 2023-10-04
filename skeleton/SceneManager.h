#pragma once
#include "Render/Camera.h"
#include "Particle.h"
#include <vector>

using namespace std;

class SceneManager
{
private:
	vector<Particle*> projectiles;
	Camera* cam;
	double LIMIT_ON_SCREEN = 20.0;

public:
	SceneManager() noexcept;

	~SceneManager();

	void addProjectile(PROJECTILE_TYPE type);

	void update(double t);

	inline void setAlive(Particle* e, bool alive) { e->alive = alive; }
};

