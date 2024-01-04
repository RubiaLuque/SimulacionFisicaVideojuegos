#include "GameManager.h"

GameManager::GameManager(PxPhysics* gPhysics, PxScene* gScene)
{
	cam = GetCamera();
	this->gPhysics = gPhysics;
	this->gScene = gScene;
}

GameManager::~GameManager()
{
	//Elimina el sistema de particulas
	for (int i = 0; i < sys.size(); ++i) {
		if (sys.at(i) != nullptr) {
			delete sys.at(i);
			sys.at(i) = nullptr;
		}
	}
	sys.clear();

	//Elimina las fuerzas de particulas
	for (int i = 0; i < forces.size(); ++i) {
		if (forces.at(i) != nullptr) {
			delete forces.at(i);
			forces.at(i) = nullptr;
		}
	}
	forces.clear();

	//Elimina las fuerzas de los solidos rigidos
	for (int i = 0; i < solidForces.size(); ++i) {
		if (solidForces.at(i) != nullptr) {
			delete solidForces.at(i);
			solidForces.at(i) = nullptr;
		}
	}
	solidForces.clear();
}

void GameManager::addProjectile(PROJECTILE_TYPE type)
{
	Vector3 vel = cam->getDir();
	const Vector3 pos = cam->getEye();
	Vector3 aVel = { 0,0,0 };

	auto s = new SolidRigid(pos, vel, aVel, type, gPhysics, gScene);
	projectiles.push_back(s);
}

void GameManager::chooseMode(char key)
{
	if (key == '1') {
		gm = EASY;
		setUpScene();
	}
	else if (key == '2') {
		gm = MEDIUM;
		setUpScene();
	}
	else if (key == '3') {
		gm = HARD;
		setUpScene();
	}
}

void GameManager::setUpScene()
{
	if (gm = EASY) {
		easyMode();
	}
	else if (gm = MEDIUM) {
		mediumMode();
	}
	else if (gm = HARD) {
		hardMode();
	}
}

void GameManager::easyMode()
{
	Vector3 vel = cam->getDir();
	const Vector3 pos = cam->getEye();

	//auto fire_target = new Target(pos, )
}

void GameManager::mediumMode()
{

}

void GameManager::hardMode()
{

}

void GameManager::update(double t)
{
	//eliminar aquellas que lleven mas tiempo del necesario en pantalla
	for (auto it = projectiles.begin(); it != projectiles.end(); it++) {
		(*it)->limit_time += t;
		if ((*it)->limit_time > Data::LIMIT_ON_SCREEN) {
			//se marca como no vivo
			setAlive(*it, false);
		}
	}

	projectiles.erase(remove_if(projectiles.begin(), projectiles.end(),
		[](SolidRigid* p) noexcept {
			if (p->alive) return false;
			else { //si no esta vivo, se elimina
				delete p;
				return true;
			}
		}), projectiles.end());

	//se hace update de todas las demas
	for (auto* solid : projectiles) {
		solid->update(t);
	}

}
