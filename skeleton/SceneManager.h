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

public:
	SceneManager() {
		cam = GetCamera();
	}

	~SceneManager() {
		delete cam;

		for (int i = 0; i < projectiles.size(); ++i) {
			delete projectiles.at(i);
		}
		delete[] &projectiles;
	}

	void addProjectile(PROJECTILE_TYPE type) {
		Vector3 vel = cam->getDir();
		Vector3 pos = cam->getEye();
		if (type == FIREBALL) {
			vel *= 10;
			Vector3 acc = { 0.0, -0.6, 0.0};
			projectiles.push_back(new Particle(pos, vel, acc, 3.0, 0.888, FIREBALL));
		}
		else if (type == LIGHTGUN)
		{
			vel *= 25;
			Vector3 acc = { 0.0, 0.0, 0.0 }; //no tiene efecto gravedad
			projectiles.push_back(new Particle(pos, vel, acc, 1.0, 0.998, LIGHTGUN));
		}
		else if (type == GUN) {
			vel *= 20;
			Vector3 acc = { 0.0, -1.0, 0.0 };
			projectiles.push_back(new Particle(pos, vel, acc, 1.0, 0.998, GUN));
		}
		else //cannon
		{
			vel *= 18;
			Vector3 acc = { 0.0, -5.0, 0.0 };
			projectiles.push_back(new Particle(pos, vel, acc, 5.0, 0.998, CANNON));
		}

	}

	void update(double t) {
		/*for (int i = 0; i < projectiles.size(); ++i) {
			if(projectiles.at(i).time_limit>)
		}*/

		for (int i = 0; i < projectiles.size(); ++i) {
			projectiles.at(i)->update(t);
		}
	}
};

