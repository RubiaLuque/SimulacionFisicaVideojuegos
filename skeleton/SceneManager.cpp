#include "SceneManager.h"

SceneManager::SceneManager() {
	cam = GetCamera();
	sys = new ParticleSystem(Data::NIEBLA);
	particleSys = true;
}

SceneManager::~SceneManager() {

	for (int i = 0; i < particles.size(); ++i) {
		if (particles.at(i) != nullptr) {
			delete particles.at(i);
			particles.at(i) = nullptr;

		}
	}
	delete[]& particles;
	delete cam;
	delete sys;
}

void SceneManager::addProjectile(PROJECTILE_TYPE type) {
	Vector3 vel = cam->getDir();
	const Vector3 pos = cam->getEye();

	if (type == FIREBALL) {
		vel *= 10;
		const Vector3 acc = { 0.0, -0.6, 0.0 }; //muy poca gravedad porque se quiere simular que flota un poco
		particles.push_back(new Particle(pos, vel, acc, 3.0, 0.888, FIREBALL));
	}
	else if (type == LIGHTGUN)
	{
		vel *= 25;
		Vector3 acc = { 0.0, 0.0, 0.0 }; //no tiene efecto gravedad
		particles.push_back(new Particle(pos, vel, acc, 1.0, 0.998, LIGHTGUN));
	}
	else if (type == GUN) {
		vel *= 20;
		const Vector3 acc = { 0.0, -1.0, 0.0 }; //poco efecto de la gravedad
		particles.push_back(new Particle(pos, vel, acc, 1.0, 0.998, GUN));
	}
	else //cannon
	{
		vel *= 18;
		const Vector3 acc = { 0.0, -5.0, 0.0 }; //bastante efecto de gravedad
		particles.push_back(new Particle(pos, vel, acc, 5.0, 0.998, CANNON));
	}

}



void SceneManager::update(double t) {
	if (!particleSys) {
		//eliminar aquellas que lleven mas tiempo del necesario en pantalla
		for (int i = 0; i < particles.size(); ++i) {
			particles.at(i)->limit_time += t;
			if (particles.at(i)->limit_time > LIMIT_ON_SCREEN) {
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

		//se hace update de todas las demas
		for (int i = 0; i < particles.size(); ++i) {
			particles.at(i)->update(t);
		}

	}
	else {
		sys->update(t);
	}
}


