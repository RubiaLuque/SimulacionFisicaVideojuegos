#include "GameManager.h"

GameManager::GameManager(PxPhysics* gPhysics, PxScene* gScene)
{
	cam = GetCamera();
	this->gPhysics = gPhysics;
	this->gScene = gScene;
}

GameManager::~GameManager()
{
	//Elimina el vector de proyectiles de particulas
	for (int i = 0; i < pProjectiles.size(); ++i) {
		if (pProjectiles.at(i) != nullptr) {
			delete pProjectiles.at(i);
			pProjectiles.at(i) = nullptr;

		}
	}
	pProjectiles.clear();

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

	//Elimina los proyectiles de solidos rigidos
	for (int i = 0; i < sProjectiles.size(); ++i) {
		if (sProjectiles.at(i) != nullptr) {
			delete sProjectiles.at(i);
			sProjectiles.at(i) = nullptr;

		}
	}
	sProjectiles.clear();

	//Elimina los sistemas de solidos rigidos
	for (int i = 0; i < solidSys.size(); ++i) {
		if (solidSys.at(i) != nullptr) {
			delete solidSys.at(i);
			solidSys.at(i) = nullptr;
		}
	}
	solidSys.clear();

	//Elimina las fuerzas de los solidos rigidos
	for (int i = 0; i < solidForces.size(); ++i) {
		if (solidForces.at(i) != nullptr) {
			delete solidForces.at(i);
			solidForces.at(i) = nullptr;
		}
	}
	solidForces.clear();
}

void GameManager::chooseMode(char key)
{
	if (key == '1') gm = GAME_MODE::PARTICLE;
	else if (key == '2') gm = GAME_MODE::SOLID_RIGID;
}

void GameManager::setUpScene()
{

}

void GameManager::update(double t)
{

}
