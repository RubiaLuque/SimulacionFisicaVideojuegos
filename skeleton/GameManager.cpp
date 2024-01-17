#include "GameManager.h"
#include "WindForceGenerator.h"

GameManager::GameManager(PxPhysics* gPhysics, PxScene* gScene)
{
	cam = GetCamera();
	this->gPhysics = gPhysics;
	this->gScene = gScene;
	score = new Score();
	sFr = new ForceRegistry<SolidRigid>();
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

	delete windForce;
	delete vortexForce;
	delete sFr;
	delete fr;
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
	fogSys->setGeneratorPos({ 0,50,-70 }, Data::NIEBLA);

	fogSys->addForce(Data::WIND, {0,50,-70});

}

void GameManager::mediumMode()
{
	auto fire_target = new Target({ 100,30,0 }, { 0,0,0 }, { 0,1,0 }, 20, Data::ORANGE, gPhysics, gScene);
	targets.push_back(fire_target);

	auto laser_target = new Target({ 80, -30, 0 }, { 0,0,0 }, { 0,1,0 }, 20, Data::BLUE, gPhysics, gScene);
	targets.push_back(laser_target);

	auto general_target = new Target({ 60, 30, 0 }, { 0,0,0 }, { 0,1,0 }, 20, Data::WHITE, gPhysics, gScene);
	targets.push_back(general_target);

	auto arrow_target = new Target({ 40, -30,0 }, { 0,0,0 }, { 0,1,0 }, 20, Data::RED, gPhysics, gScene);
	targets.push_back(arrow_target);

	auto bullet_target = new Target({ 20, 30, 0 }, { 0,0,0 }, { 0,1,0 }, 20, Data::BLACK, gPhysics, gScene);
	targets.push_back(bullet_target);

	auto fire_target1 = new Target({ 0,-30,0 }, { 0,0,0 }, { 0,1,0 }, 20, Data::ORANGE, gPhysics, gScene);
	targets.push_back(fire_target1);

	auto laser_target1 = new Target({ -20, 30, 0 }, { 0,0,0 }, { 0,1,0 }, 20, Data::BLUE, gPhysics, gScene);
	targets.push_back(laser_target1);

	auto general_target1 = new Target({ -40, -30, 0 }, { 0,0,0 }, { 0,1,0 }, 20, Data::WHITE, gPhysics, gScene);
	targets.push_back(general_target1);

	auto arrow_target1 = new Target({ -60, 30, 0 }, { 0,0,0 }, { 0,1,0 }, 20, Data::RED, gPhysics, gScene);
	targets.push_back(arrow_target1);

	auto bullet_target1 = new Target({ -80, -30, 0 }, { 0,0,0 }, { 0,1,0 }, 20, Data::BLACK, gPhysics, gScene);
	targets.push_back(bullet_target1);

	auto targetSys = new SolidRigidSystem(Data::NONE, gPhysics, gScene);
	solidSys.push_back(targetSys);
	//targetSys->generateSpringTargets()

	auto fogSys = new ParticleSystem(Data::NIEBLA, gPhysics, gScene);
	fogSys->setGeneratorPos({ 0,50,0 }, Data::NIEBLA);
	sys.push_back(fogSys);

	auto snowSys = new ParticleSystem(Data::NIEVE, gPhysics, gScene);
	snowSys->setGeneratorPos({ 20,80,0 }, Data::NIEVE);
	sys.push_back(snowSys);

	snowSys->addForce(Data::VORTEX, { 20,50,0 });
}

void GameManager::hardMode()
{
	Vector3 pos = { 5,5,5 };
	auto staticR = new SolidRigid(pos, { 0,0,0 }, { 0,0,0 }, { 0.1, 0.1, 0.1, 0.0 }, 0.5, 1, Data::_STATIC, gPhysics, gScene);

	for (int i = 0; i <5; ++i) {
		float a = i * 3.0f *PxPi / 5.0f;

		float x = pos.x + std::cos(a);
		float y = pos.y +30+ std::sin(a) + i*20;
		float z = pos.z + 30 +i*20;

		int random = rand() % 4;
		Data::TARGET_MODE mode = (Data::TARGET_MODE)random;
		auto target = new Target({ x,y,z }, { 0,0,0 }, { 0,0,0 }, 10, mode, gPhysics, gScene);
		targets.push_back(target);

		PxRevoluteJoint* joint = PxRevoluteJointCreate(*gPhysics, staticR->getRigidActor(), 
			staticR->getTransform(), target->getRigidActor(), target->getTransform());
		joint->setDriveVelocity(1.0f); 
		joint->setRevoluteJointFlag(PxRevoluteJointFlag::eDRIVE_ENABLED, true);

	}

	Vector3 pos1 = { 0,50,0 };
	auto staticR1 = new SolidRigid(pos, { 0,0,0 }, { 0,0,0 }, { 0.1, 0.1, 0.1, 0.0 }, 0.5, 1, Data::_STATIC, gPhysics, gScene);
	int random = rand() % 4;
	float x1 = pos1.x + 30;
	float y1 = pos1.y + 30;
	float z1 = pos1.z + 30;
	Data::TARGET_MODE mode1 = (Data::TARGET_MODE)random;
	auto target1 = new Target({ x1,y1,z1 }, { 0,0,0 }, { 0,0,0 }, 10, mode1, gPhysics, gScene);
	targets.push_back(target1);

	PxRevoluteJoint* joint1 = PxRevoluteJointCreate(*gPhysics, staticR1->getRigidActor(),
		staticR1->getTransform(), target1->getRigidActor(), target1->getTransform());
	joint1->setDriveVelocity(2.0f);
	joint1->setRevoluteJointFlag(PxRevoluteJointFlag::eDRIVE_ENABLED, true);

	Vector3 pos2 = { 40,5,5 };
	auto staticR2 = new SolidRigid(pos2, { 0,0,0 }, { 0,0,0 }, { 0.1, 0.1, 0.1, 0.0 }, 0.5, 1, Data::_STATIC, gPhysics, gScene);

	for (int i = 0; i < 3; ++i) {
		float a = i * 3.0f * PxPi / 3.0f;

		float x2 = pos2.x + std::cos(a);
		float y2 = pos2.y + 30 + std::sin(a) + i * 30;
		float z2 = pos2.z + 30 + i * 20;

		int random2 = rand() % 5;
		Data::TARGET_MODE mode2 = (Data::TARGET_MODE)random2;
		auto target2 = new Target({ x2,y2,z2 }, { 0,0,0 }, { 0,0,0 }, 10, mode2, gPhysics, gScene);
		targets.push_back(target2);

		PxRevoluteJoint* joint2 = PxRevoluteJointCreate(*gPhysics, staticR2->getRigidActor(),
			staticR2->getTransform(), target2->getRigidActor(), target2->getTransform());
		joint2->setDriveVelocity(4.0f);
		joint2->setRevoluteJointFlag(PxRevoluteJointFlag::eDRIVE_ENABLED, true);

	}

	auto fogSys = new ParticleSystem(Data::NIEBLA, gPhysics, gScene);
	fogSys->setGeneratorPos({ 0,50,0 }, Data::NIEBLA);
	sys.push_back(fogSys);

}

void GameManager::update(double t)
{
	_score = score->getScore();
	if (mode != 0) {
		endGame();
		if (end) {
			mode = 4;
			endSystem->update(t);
			//return;
		}
	}

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

	sFr->updateForces(t);

	if (targets.size() > 0) {
		targets.erase(remove_if(targets.begin(), targets.end(),
			[](Target* p) noexcept {
				if (p->alive) return false;
				else { //si no esta vivo, se elimina
					delete p;
					return true;
				}
			}), targets.end());

	}

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
			score->addScore((*target)->getType());
			_score = score->getScore();

			//Se invoca a un firework y se guarda en la lista para hacer update
			auto firework = new Firework(pos, color);
			fireworks.push_back(firework);
		}

	}
}


void GameManager::endGame()
{
	if (targets.size() == 0 && !check) {
		end = true;
		deleteElements();
		endSystem = new ParticleSystem(Data::NONE, gPhysics, gScene);
		endSystem->generateSlinky();
		check = true;
		
	}
}

void GameManager::deleteElements()
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
	for (int i = 0; i < projectiles.size(); ++i) {
		if (projectiles.at(i) != nullptr) {
			delete projectiles.at(i);
			projectiles.at(i) = nullptr;
		}
	}
	projectiles.clear();

	//Elimina los fireworks
	for (int i = 0; i < fireworks.size(); ++i) {
		if (fireworks.at(i) != nullptr) {
			delete fireworks.at(i);
			fireworks.at(i) = nullptr;
		}
	}
	fireworks.clear();

	delete windForce;
	delete vortexForce;
}
