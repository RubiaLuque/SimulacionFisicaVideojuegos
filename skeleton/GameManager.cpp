#include "GameManager.h"
#include "WindForceGenerator.h"

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


	//Se eliminan los sistemas de solidos rigidos
	for (int i = 0; i < solidSys.size(); ++i) {
		if (solidSys.at(i) != nullptr) {
			delete solidSys.at(i);
			solidSys.at(i) = nullptr;
		}
	}
	solidSys.clear();

	//Elimina los proyectiles
	for(int i = 0; i < projectiles.size(); ++i) {
		if (projectiles.at(i) != nullptr) {
			delete projectiles.at(i);
			projectiles.at(i) = nullptr;
		}
	}
	projectiles.clear();

	//Elimina las dianas
	for (int i = 0; i < targets.size(); ++i) {
		if (targets.at(i) != nullptr) {
			delete targets.at(i);
			targets.at(i) = nullptr;
		}
	}
	targets.clear();
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
	if (gm == EASY) {
		easyMode();
	}
	else if (gm == MEDIUM) {
		mediumMode();
	}
	else if (gm == HARD) {
		hardMode();
	}
}

void GameManager::easyMode()
{
	Vector3 vel = cam->getDir();
	const Vector3 pos = cam->getEye();

	auto fire_target = new Target({0,20,0}, {0,0,0}, {0,0,0}, 20, Data::ORANGE, gPhysics, gScene);
	targets.push_back(fire_target);

	auto laser_target = new Target({ 100, 20, 0 }, { 0,0,0 }, { 0,0,0 }, 20, Data::BLUE, gPhysics, gScene);
	targets.push_back(laser_target);

	auto general_target = new Target({ -100, 100, 0 }, { 0,0,0 }, { 0,0,0 }, 20, Data::WHITE, gPhysics, gScene);
	targets.push_back(general_target);

	auto arrow_target = new Target({ -130, -100, 0 }, { 0,0,0 }, { 0,0,0 }, 20, Data::RED, gPhysics, gScene);
	targets.push_back(arrow_target);

	auto bullet_target = new Target({ 0, 50, -100 }, { 0,0,0 }, { 0,1,0 }, 20, Data::BLACK, gPhysics, gScene);
	targets.push_back(bullet_target);

	auto targetSys = new SolidRigidSystem(Data::NONE, gPhysics, gScene);
	solidSys.push_back(targetSys);

	auto fogSys = new ParticleSystem(Data::NIEBLA, gPhysics, gScene);
	sys.push_back(fogSys);

	//targetSys->generateSpringTargets(general_target, arrow_target);
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
		if (windForce != nullptr) sFr->addRegistry(windForce, solid);
		if (vortexForce != nullptr) sFr->addRegistry(vortexForce, solid);
		solid->update(t);
	}

	targets.erase(remove_if(targets.begin(), targets.end(),
		[](Target* p) noexcept {
			if (p->alive) return false;
			else { //si no esta vivo, se elimina
				delete p;
				return true;
			}
		}), targets.end());

	//Se actualizan las dianas
	for (auto* target : targets) {
		target->update(t);
	}

	//Se actualizan los fireworks
	for (auto* fire : fireworks) {
		fire->update(t);
	}

	//Se actualizan los sistemas de solidos rigidos
	for (auto sys : solidSys) {
		sys->update(t);
	}

	//Se actualizan los sistemas de particulas
	for (auto s : sys) {
		s->update(t);
	}

	
	
}

//Comprueba las colisiones entre dianas y projectiles
void GameManager::onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{

	auto& target = std::find_if(targets.begin(), targets.end(), [actor1, actor2](Target* t) {
		return t->getActor() == actor1 || t->getActor() == actor2;

		});

	
	auto& p = std::find_if(projectiles.begin(), projectiles.end(), [actor1, actor2](SolidRigid* s) {
		return s->getActor() == actor1 || s->getActor() == actor2;

		});

	if (target != targets.end() && p != projectiles.end()) {
		if ((*target)->getType() == (*p)->getType() || (*target)->getType() == Data::WHITE) {
			//Nos guardamos el color y la posicion de la diana entes de eliminarla para despues usarlo en el firework
			auto color = (*target)->getColor();
			auto pos = (*target)->getPos();

			//Se eliminan la diana y el proyectil
			setAlive((*target), false);
			setAlive((*p), false);

			//Se suma la puntuacion


			//Se invoca a un firework y se guarda en la lista para hacer update
			auto firework = new Firework(pos, color);
			fireworks.push_back(firework);
		}

	}
}

void GameManager::createWind()
{
	windForce = new WindForceGenerator<SolidRigid>({0,20,2});
	Vector3 pos;
	pos.x = rand() % 50;
	pos.y = rand() % 50;
	pos.z = rand() % 50;
	windForce->setPos(pos);

}
