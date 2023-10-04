#include "SceneManager.h"

SceneManager::SceneManager() noexcept {
	cam = GetCamera();
}

SceneManager::~SceneManager() {
	delete cam;

	for (int i = 0; i < projectiles.size(); ++i) {
		delete projectiles.at(i);
		projectiles.at(i) = nullptr;
	}
	delete[]& projectiles;
}

void SceneManager::addProjectile(PROJECTILE_TYPE type) {
	Vector3 vel = cam->getDir();
	const Vector3 pos = cam->getEye();

	if (type == FIREBALL) {
		vel *= 10;
		const Vector3 acc = { 0.0, -0.6, 0.0 };
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
		const Vector3 acc = { 0.0, -1.0, 0.0 };
		projectiles.push_back(new Particle(pos, vel, acc, 1.0, 0.998, GUN));
	}
	else //cannon
	{
		vel *= 18;
		const Vector3 acc = { 0.0, -5.0, 0.0 };
		projectiles.push_back(new Particle(pos, vel, acc, 5.0, 0.998, CANNON));
	}

}

void SceneManager::update(double t) {
	//eliminar aquellas que lleven mas tiempo del necesario en pantalla
	for (int i = 0; i < projectiles.size(); ++i) {
		projectiles.at(i)->limit_time += t;
		if (projectiles.at(i)->limit_time > LIMIT_ON_SCREEN) {
			//se marca como no vivo
			setAlive(projectiles.at(i), false);

			projectiles.erase(remove_if(projectiles.begin(), projectiles.end(),
				[](Particle* p) {
					if (p->alive) return false;
					else { //si no esta vivo, se elimina
						delete p;
						return true;
					}
				}), projectiles.end()
					);
		}
	}

	//se hace update de todas las demas
	for (int i = 0; i < projectiles.size(); ++i) {
		projectiles.at(i)->update(t);
	}
}


