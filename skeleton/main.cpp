#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "Render/Camera.h"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "SceneManager.h"

//#include "Particle.h"

#include <iostream>

std::string display_text = "This is a test";


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;
SceneManager* manager;

float timeKey = 0;
bool keyPressed = false;

PxPhysics* getPhysics() noexcept { return gPhysics; }
PxScene* getScene() noexcept { return gScene; }


//partícula practica 1
//Particle* particle; -->Descomentar para usar una sola particula en MRU

// Initialize physics engine
//Codigo de inicializacion
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425.0, 10.0);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	//metodo que crea la fisica del motor
	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	//material con coeficientes de rozamiento estatico, dinamico y elasticidad
	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	//PRACTICA 5 -> SÓLIDOS RÍGIDOS
	//Generar suelo
	//PxRigidStatic* suelo = gPhysics->createRigidStatic(PxTransform({ 0,0,0 }));
	//PxShape* shape = CreateShape(PxBoxGeometry(100, 0.1, 100));
	//suelo->attachShape(*shape); //Se enlaza la caja con un solido rigido
	//gScene->addActor(*suelo); //Se añade el solido rigido a la escena
	////Pintar el suelo
	//RenderItem* item;
	//item = new RenderItem(shape, suelo, { 0.8, 0.8, 0.8, 1 });

	//Rigid bodies dinamicos
	//PxRigidDynamic* new_solid;
	//new_solid = gPhysics->createRigidDynamic(PxTransform({ -70, 200, -70 }));
	//new_solid->setLinearVelocity({ 0,5,0 });
	//new_solid->setAngularVelocity({ 0,0,0 });
	//PxShape* new_shape = CreateShape(PxBoxGeometry(5, 5, 5));
	//new_solid->attachShape(*new_shape);
	//PxRigidBodyExt::updateMassAndInertia(*new_solid, 0.15);
	//gScene->addActor(*new_solid);
	////Pintar el nuevo solido rigido dinamico
	//RenderItem* dynamic_solid;
	//dynamic_solid = new RenderItem(new_shape, new_solid, { 0.2, 0.2, 0.2, 1 });


	//particula - PRACTICA 1
	//particle = new Particle(PxVec3(1.0, 1.0, 1.0), PxVec3(0.0, 5.0, 0.0), PxVec3(0.0, 6.0, 0.0), 1.0, 0.998);

	manager = new SceneManager();
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds

//Aqui se hacen las actualizaciones del mundo en el que se trabaja
//Llamadas a actualizacion de escenas
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(t);
	gScene->fetchResults(true);
	//particle->update(t); --> actualiza la particula inicial
	
	manager->update(t);
	if (keyPressed) {
		timeKey += t;
		if (timeKey > Data::MAX_TIME_KEY) {
			keyPressed = false;
			timeKey = 0;
		}
	}
}

// Function to clean data
// Add custom code to the begining of the function
//Se limpia la memoria usada
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();

	gFoundation->release();

	//delete particle; --> para eliminar la particula inicial

	delete manager;
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{//la camara tambien se mueve con teclas que estan reservadas para ello

	PX_UNUSED(camera);

	switch (toupper(key))
	{
		//case ' ':	break;
	case '1': //casts a fireball
	{
		if (!keyPressed && timeKey <= Data::MAX_TIME_KEY) {
			manager->addProjectile(FIREBALL);
			timeKey = 0;
		}
		break;
	}
	case '2': //shoots a lightgun
	{
		if (!keyPressed && timeKey <= Data::MAX_TIME_KEY) {
			manager->addProjectile(LIGHTGUN);
			timeKey = 0;
		}
		break;
	}
	case '3': { //shoots a bullet
		if (!keyPressed && timeKey <= Data::MAX_TIME_KEY) {
			manager->addProjectile(GUN);
			timeKey = 0;
		}
		break;
	}
	case '4': { //fires a cannon
		if (!keyPressed && timeKey <= Data::MAX_TIME_KEY) {
			manager->addProjectile(CANNON);
			timeKey = 0;
		}
		break;
	}
	case 'F': { //fireworks
		if (!keyPressed && timeKey <= Data::MAX_TIME_KEY) {
			manager->addFirework();
			timeKey = 0;
		}
		break;
	}
	case '5': {
		if (!keyPressed && timeKey <= Data::MAX_TIME_KEY) {
			manager->addParticleSystem(FUENTE);
			timeKey = 0;
		}
		break;
	}
	case '6': {
		if (!keyPressed && timeKey <= Data::MAX_TIME_KEY) {
			manager->addParticleSystem(LLUVIA);
			timeKey = 0;
		}
		break;
	}
	case '7': {
		if (!keyPressed && timeKey <= Data::MAX_TIME_KEY) {
			manager->addParticleSystem(NIEVE);
			timeKey = 0;
		}
		break;
	}
	case '8': {
		if (!keyPressed && timeKey <= Data::MAX_TIME_KEY) {
			manager->addParticleSystem(NIEBLA);
			timeKey = 0;
		}
		break;
	}
	case 'Z': {
		if (!keyPressed && timeKey <= Data::MAX_TIME_KEY) {
			manager->addForceToSystem(WIND);
			timeKey = 0;
		}
		break;
	}
	case 'V': {
		if (!keyPressed && timeKey <= Data::MAX_TIME_KEY) {
			manager->addForceToSystem(VORTEX);
			timeKey = 0;
		}
		break;
	}
	case 'X': {
		if (!keyPressed && timeKey <= Data::MAX_TIME_KEY) {
			manager->addForceToSystem(EXPLOSION);

			timeKey = 0;
		}
		break;
	}
	case 'C':
		if (!keyPressed && timeKey <= Data::MAX_TIME_KEY) {
			manager->generateSpring();

			timeKey = 0;
		}
		break;
	case 'B':
		if (!keyPressed && timeKey <= Data::MAX_TIME_KEY) {
			manager->generateSlinky();

			timeKey = 0;
		}
		break;
	case 'N':
		if (!keyPressed && timeKey <= Data::MAX_TIME_KEY) {
			manager->generateBuoyancyWater();

			timeKey = 0;
		}
		break;
	case 'M':
		if (!keyPressed && timeKey <= Data::MAX_TIME_KEY) {
			manager->generateBuoyancyMercury();

			timeKey = 0;
		}
		break;
	case 'P':
		if (!keyPressed && timeKey <= Data::MAX_TIME_KEY) {
			manager->setK(0);

			timeKey = 0;
		}
		break;
	case 'O':
		if (!keyPressed && timeKey <= Data::MAX_TIME_KEY) {
			manager->setK(1);

			timeKey = 0;
		}
		break;
	default:
		break;
	}
	keyPressed = true;
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}